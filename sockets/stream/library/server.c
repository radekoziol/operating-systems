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
int sockfd_innet = -1, sockfd_unix = -1;

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

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

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

#pragma clang diagnostic pop

void force_stop(int signum) {

    pthread_cancel(ping_thread);
    for (int i = 0; i < cl_counter; i++)
        free(cl_names[i]);

    close(sockfd_unix);
    close(sockfd_innet);
}

bool name_exist(char *response) {

    for (int i = 0; i < MAX_CLIENT_NUM; i++)
        if (cl_names[i] != NULL && strcmp(cl_names[i], response) == 0)
            return true;


}

void run_innet_sock(int portno, char *host_addr) {

    struct sockaddr_in serv_addr_innet;


    if ((sockfd_innet = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error_and_die("socket: error while opening socket\n");

    if (setsockopt(sockfd_innet, SOL_SOCKET, SO_REUSEADDR, &(int) {1}, sizeof(int)) < 0)
        error_and_die("setsockopt(SO_REUSEADDR) failed");

    make_unblocking(sockfd_innet);


    bzero((char *) &serv_addr_innet, sizeof(serv_addr_innet));

    portno = 51717;
    serv_addr_innet.sin_family = AF_INET;
    serv_addr_innet.sin_addr.s_addr = inet_addr(host_addr);
    serv_addr_innet.sin_port = htons(portno);

    if (bind(sockfd_innet, (struct sockaddr *) &serv_addr_innet, sizeof(serv_addr_innet)) < 0)
        error_and_die("bind: ERROR on binding\n");

}

void run_unix_sock(char *addr) {

    if ((sockfd_unix = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
        error_and_die("socket: error while opening socket\n");

    if (setsockopt(sockfd_unix, SOL_SOCKET, SO_REUSEADDR, &(int) {1}, sizeof(int)) < 0)
        error_and_die("setsockopt(SO_REUSEADDR) failed");

    make_unblocking(sockfd_unix);

    struct sockaddr_un serv_addr_unix = {AF_UNIX, addr};

    if (bind(sockfd_unix, (struct sockaddr *) &serv_addr_unix, sizeof(serv_addr_unix)) < 0)
        error_and_die("bind: ERROR on binding\n");


}

int create_epoll(int *efd, struct epoll_event *event) {


    if ((*efd = epoll_create1(0)) < 0) {
        perror("Epoll initialization error");
        exit(-1);
    }



    if (sockfd_unix != -1) {
        listen(sockfd_unix, 5);
        if (epoll_ctl(*efd, EPOLL_CTL_ADD, sockfd_unix, event) < 0) {
            perror("Epoll error adding socket");
            exit(-1);
        }

    } else if (sockfd_innet != -1) {
        listen(sockfd_innet, 5);

        if (epoll_ctl(*efd, EPOLL_CTL_ADD, sockfd_innet, event) < 0) {
            perror("Epoll error adding socket");
            exit(-1);
        }
    }


}

int main(int argc, char *argv[]) {

    // Example input
    argc = 3;
    argv[1] = "127.0.0.1";
    argv[2] = "51717";

    if (argc == 1) {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }

    char *host_addr, *unix_addr;
    int portnum;

    if (argc == 2) {
        unix_addr = argv[1];
        run_unix_sock(unix_addr);
    } else {
        host_addr = argv[1];
        portnum = (int) strtol(argv[2], NULL, 10);
        run_innet_sock(portnum, host_addr);
    }

    signal(SIGINT, &force_stop);

    memset(cl_names, NULL, MAX_CLIENT_NUM);

    struct epoll_event event;
    event.data.fd = sockfd_innet;
    event.events = EPOLLIN;

    int efd;
    create_epoll(&efd,&event);

    events = (struct epoll_event *) calloc(MAX_CLIENT_NUM, sizeof(event));
    if (!events) {
        perror("Error allocating event buffers");
        exit(-1);
    }

    pthread_create(&ping_thread, NULL, (void *(*)(void *)) ping_clients, NULL);


    while (1) {

        int n = 0;
        printf("Calling epoll_wait\n");
        if ((n = epoll_wait(efd, events, MAX_CLIENT_NUM, -1)) == -1) {
            perror("epoll_wait failure");
            exit(-1);
        }

        for (int i = 0; i < n; i++) {
            printf("Checking event for fd = %d\n", events[i].data.fd);

            if (sockfd_innet == events[i].data.fd) {
                accept_connection(sockfd_innet, efd);
            } else {
                char response[256];
                strcpy(response, receive_response(events[i].data.fd));

                if (cl_names[events[i].data.fd] == NULL) {
                    if (name_exist(response)) {
                        send(events[i].data.fd, "This name exists!", 18, 0);
                        epoll_ctl(efd, EPOLL_CTL_DEL, events[i].data.fd, &event);
                    } else {
                        cl_names[events[i].data.fd] = malloc(strlen(response));
                        strcpy(cl_names[events[i].data.fd], response);
                        printf("Name: %s\n", cl_names[events[i].data.fd]);
                        send_operation(events[i].data.fd);
                    }
                } else {
                    printf("Response from %s: %s\n", cl_names[events[i].data.fd], response);
//                    epoll_ctl(efd, EPOLL_CTL_DEL, events[i].data.fd, &event);
                    close(events[i].data.fd);
                }

            }

        }

    }

}