#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <memory.h>
#include <bits/fcntl-linux.h>
#include <mqueue.h>
#include <signal.h>
#include <zconf.h>
#include "main.h"
//
// Created by radekkoziol on 24.04.18.
//

#define BILLION 1000000000L

void error_and_die(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}


void print_time(char *msg) {

    printf("%s", msg);
    clock_gettime(CLOCK_MONOTONIC_RAW, &end);    /* mark the end time */
    uint64_t diff = (uint64_t) (BILLION * (end.tv_sec - start.tv_sec) + end.tv_nsec - start.tv_nsec);

    char time[32];
    memset(time, '\0', 32);
    float seconds = (float) (diff / 1000000000.0);

    printf(" - time = %f seconds\n", seconds);
}

int server_open() {

    mqd_t mqd;

    if ((mqd = mq_open(SERVER_NAME, O_WRONLY)) == -1) {
        perror("mq_open() error");
        exit(-1);
    }

    struct mq_attr attr;
    mq_getattr(mqd, &attr);

    printf("Queue successfully open with following attributes: \n");
    printf("max #msgs = %ld,max #bytes/msg = %ld,#currently on queue = %ld\n",
           attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);

    return mqd;
}


void stop_program(int signum) {
    got_sigint_signal = 1;
}


int server_up() {

    // Setting handler for stopping
    struct sigaction action, sa;

    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_handler = &stop_program;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return EXIT_FAILURE;
    }
    sigaction(SIGINT, NULL, &action);

    struct mq_attr attr;
    attr.mq_flags = O_NONBLOCK;
    attr.mq_maxmsg = MAX_MSG;
    attr.mq_msgsize = MSG_SIZE;
    attr.mq_curmsgs = 0;

    mqd_t mqd;

    if ((mqd = mq_open(SERVER_NAME, O_CREAT | O_RDONLY, 0644, &attr)) == -1) {
        perror("mq_open() error");
        exit(-1);
    }

    printf("Queue successfully created with following attributes: \n");
    mq_getattr(mqd, &attr);
    printf("max #msgs = %ld,max #bytes/msg = %ld,#currently on queue = %ld\n",
           attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);

    return mqd;
}

void cut_client(pid_t pid) {

    char msg[128];
    memset(msg,'\0',128);
    sprintf(msg, "%s %d","[Barber] Starting to cut client ", pid );
    print_time(msg);

    sleep(2); // brubrubu

    memset(msg,'\0',128);
    sprintf(msg, "%s %d","[Barber] Finished cut of client ", pid );
    print_time(msg);
}


void server_down(mqd_t mqd) {
    /* cleanup */
    mq_unlink(SERVER_NAME);
    mq_close(mqd);
    exit(0);
}

