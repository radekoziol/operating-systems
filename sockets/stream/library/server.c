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

struct epoll_event *events;
pthread_t ping_thread;
int sockfd, calc_id = 0;
char *cl_names[MAX_CLIENT_NUM];

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

void force_stop() {


    pthread_cancel(ping_thread);
    close(sockfd);
}

void set_signal_handler() {

    struct sigaction sa;

    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_handler = (__sighandler_t) &force_stop;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
}

bool name_exist(char *response) {

    for (int i = 0; i < MAX_CLIENT_NUM; i++)
        if (strcmp(cl_names, response) == 0)
            return true;


}

int main(int argc, char *argv[]) {

    set_signal_handler();

    memset(cl_names, NULL, MAX_CLIENT_NUM);

    int portno;
    struct sockaddr_in serv_addr;
    char *host_addr = "127.0.0.1";


//    if (argc < 2) {
//        fprintf(stderr, "ERROR, no port provided\n");
//        exit(1);
//    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        error_and_die("socket: error while opening socket\n");

    make_unblocking(sockfd);

    bzero((char *) &serv_addr, sizeof(serv_addr));

    portno = 51717;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(host_addr);
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error_and_die("bind: ERROR on binding\n");

    listen(sockfd, 5);

    int efd;
    if ((efd = epoll_create1(0)) < 0) {
        perror("Epoll initialization error");
        exit(-1);
    }

    struct epoll_event event;

    event.data.fd = sockfd;
    event.events = EPOLLIN;

    if (epoll_ctl(efd, EPOLL_CTL_ADD, sockfd, &event) < 0) {
        perror("Epoll error adding socket");
        exit(-1);
    }

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

            if (sockfd == events[i].data.fd) {
                accept_connection(sockfd, efd);
            } else {
                if (cl_names[events[i].data.fd] == NULL) {
                    char *response = receive_response(events[i].data.fd);
                    if (name_exist(response)) {
                        send(events[i].data.fd, "This name exists!", 18, 0);
                        epoll_ctl(efd, EPOLL_CTL_DEL, sockfd, &event);
                    } else {
                        cl_names[events[i].data.fd] = receive_response(events[i].data.fd);
                        printf("Name: %s\n", cl_names[events[i].data.fd]);
                        send_operation(events[i].data.fd);
                    }
                } else {
                    printf("Response: %s\n", receive_response(events[i].data.fd));
                }

            }

        }

    }

}