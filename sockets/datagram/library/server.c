#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <zconf.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <pthread.h>
#include <memory.h>
#include <signal.h>
#include <stdbool.h>

#include "utils.c"
#include "../server.h"
#include <sys/un.h>


struct epoll_event *events;
pthread_t ping_thread;
char *cl_names[MAX_CLIENT_NUM];
int sockfd_dgram = -1, sockfd_unix = -1;

void accept_connection(int sock, int epoll_fd) {
    struct epoll_event event;
    event.events = EPOLLIN;

    int insock = accept(sock, NULL, NULL);
    if (insock < 0) {
        perror("Error accepting connection");
        exit(-1);
    }

    event.data.fd = insock;

    make_unblocking(insock);

    int s = epoll_ctl(epoll_fd, EPOLL_CTL_ADD, insock, &event);
    if (s < 0) {
        perror("Epoll error adding accepted connection");
        exit(-1);
    }


    printf("Connection processed.\n");
}

void ping_clients() {

    // Blocking SIGINT
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    pthread_sigmask(SIG_BLOCK, &set, NULL);

    while (1) {

        sleep(1);

        for (int i = 0; i < MAX_CLIENT_NUM; i++) {

            if (send(events[i].data.fd, " ", 1, 0) != 1) {
                close(events[i].data.fd);
            }
        }
    }

}

void force_stop(int signum) {

    pthread_cancel(ping_thread);
    for (int i = 0; i < cl_counter; i++)
        free(cl_names[i]);

    close(sockfd_unix);
    close(sockfd_dgram);
}

bool name_exist(char *response) {

    for (int i = 0; i < MAX_CLIENT_NUM; i++)
        if (cl_names[i] != NULL && strcmp(cl_names[i], response) == 0)
            return true;

    return false;
}

void run_dgram_sock(int portno, char *host_addr) {

    struct sockaddr_in serv_addr_dgram;


    if ((sockfd_dgram = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        error_and_die("socket: error while opening socket\n");

    if (setsockopt(sockfd_dgram, SOL_SOCKET, SO_REUSEADDR, &(int) {1}, sizeof(int)) < 0)
        error_and_die("setsockopt(SO_REUSEADDR) failed");

    make_unblocking(sockfd_dgram);


    bzero((char *) &serv_addr_dgram, sizeof(serv_addr_dgram));

    serv_addr_dgram.sin_family = AF_INET;
    serv_addr_dgram.sin_addr.s_addr = inet_addr(host_addr);
    serv_addr_dgram.sin_port = htons(portno);

    if (bind(sockfd_dgram, (struct sockaddr *) &serv_addr_dgram, sizeof(serv_addr_dgram)) < 0)
        error_and_die("bind: ERROR on binding\n");

}

void run_unix_sock(char *addr) {

    if ((sockfd_unix = socket(AF_UNIX, SOCK_DGRAM, 0)) < 0)
        error_and_die("socket: error while opening socket\n");

    if (setsockopt(sockfd_unix, SOL_SOCKET, SO_REUSEADDR, &(int) {1}, sizeof(int)) < 0)
        error_and_die("setsockopt(SO_REUSEADDR) failed");

    make_unblocking(sockfd_unix);

    struct sockaddr_un serv_addr_unix;
    serv_addr_unix.sun_family = AF_UNIX;
    strcpy(serv_addr_unix.sun_path ,addr);

    if (bind(sockfd_unix, (struct sockaddr *) &serv_addr_unix, sizeof(serv_addr_unix)) < 0)
        error_and_die("bind: ERROR on binding\n");


}

int create_epoll(int *efd, struct epoll_event *event) {


    if ((*efd = epoll_create1(0)) < 0) {
        perror("Epoll initialization error");
        exit(-1);
    }


    if (sockfd_unix != -1) {
        if (epoll_ctl(*efd, EPOLL_CTL_ADD, sockfd_unix, event) < 0) {
            perror("Epoll error adding socket");
            exit(-1);
        }

    }
    else if    (sockfd_dgram != -1) {
        if (epoll_ctl(*efd, EPOLL_CTL_ADD, sockfd_dgram, event) < 0) {
            perror("Epoll error adding socket");
            exit(-1);
        }
    }

    return 1;

}

int main(int argc, char *argv[]) {

    // ip route get 8.8.8.8 | awk '{print $NF; exit}'
    // Example input
//    argc = 3;
//    argv[1] = "127.0.0.1";
//    argv[2] = "51717";
//    argv[3] = "example";

    if (argc < 3) {
        printf("Arguments are: <address> <port> <u_name> \n");
        exit(1);
    }

    run_unix_sock(argv[3]);

    int portnum = (int) strtol(argv[2], NULL, 10);
    run_dgram_sock(portnum, argv[1]);

    signal(SIGINT, &force_stop);

    struct epoll_event event;
    event.data.fd = sockfd_dgram;
    event.events = EPOLLIN;

    int efd;
    create_epoll(&efd, &event);

    events = (struct epoll_event *) calloc(MAX_CLIENT_NUM, sizeof(event));
    if (!events) {
        perror("Error allocating event buffers");
        exit(-1);
    }

    pthread_create(&ping_thread, NULL, (void *(*)(void *)) ping_clients, NULL);


    printf("unix = %d, inet = %d\n", sockfd_unix, sockfd_dgram);

    while (1) {

        int n = 0;
        printf("Calling epoll_wait\n");
        if ((n = epoll_wait(efd, events, MAX_CLIENT_NUM, -1)) == -1) {
            perror("epoll_wait failure");
            exit(-1);
        }

        for (int i = 0; i < n; i++) {
            printf("Checking event for fd = %d\n", events[i].data.fd);

            char response[256];
            strcpy(response, receive_response(events[i].data.fd));

            if (sockfd_dgram == events[i].data.fd) {
                if (name_exist(response)) {
                    send(events[i].data.fd, "This name exists!", 18, 0);
                    epoll_ctl(efd, EPOLL_CTL_DEL, events[i].data.fd, &event);
                } else {
                    cl_names[events[i].data.fd] = malloc(strlen(response));
                    strcpy(cl_names[events[i].data.fd], response);
                    printf("Name: %s\n", cl_names[events[i].data.fd]);

                    struct sockaddr_in si_other;
                    memset((char *) &si_other, 0, sizeof(si_other));
                    si_other.sin_family = AF_INET;
                    si_other.sin_port = htons(portnum);
                    if (inet_aton(argv[1] , &si_other.sin_addr) == 0)
                    {
                        fprintf(stderr, "inet_aton() failed\n");
                        exit(1);
                    }

                    char buffer[123];
                    size_t slen=sizeof(si_other);
                    sendto(events[i].data.fd, buffer, strlen(buffer) , 0 , (struct sockaddr *) &si_other, slen );

//                        send_operation(events[i].data.fd);
                }
            } else {

                printf("Response from %s: %s\n", cl_names[events[i].data.fd], response);
//                    epoll_ctl(efd, EPOLL_CTL_DEL, events[i].data.fd, &event);
                close(events[i].data.fd);

            }

        }

    }

}