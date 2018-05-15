#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdint.h>
#include <memory.h>
#include <mqueue.h>
#include <signal.h>
#include <zconf.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include "main.h"

//
// Created by radekkoziol on 24.04.18.
//
int msgqid;
struct barbershop *barber_s;

#define MSGPERM 0600    // msg queue permission
#define BILLION 1000000000L

void error_and_die(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void set_time(struct barbershop *b_s) {
    barber_s = b_s;
    clock_gettime(CLOCK_MONOTONIC_RAW, &barber_s->start);    /* mark start time */
}

void print_time(char *msg) {

    printf("%s", msg);
    struct timespec end;

    clock_gettime(CLOCK_MONOTONIC_RAW, &end);    /* mark the end time */
    uint64_t diff = (uint64_t) (BILLION * (end.tv_sec - barber_s->start.tv_sec) + end.tv_nsec -
                                barber_s->start.tv_nsec);

    float seconds = (float) (diff / 1000000000.0);

    printf(" - time = %f seconds\n", seconds);
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


    // Initializing queue
    msgqid = msgget(IPC_PRIVATE, MSGPERM | IPC_CREAT | IPC_EXCL);
    if (msgqid < 0) {
        perror(strerror(errno));
        printf("failed to create message queue with msgqid = %d\n", msgqid);
        return 1;
    }

    return msgqid;
}

void cut_client(pid_t pid) {

    char msg[128];
    memset(msg, '\0', 128);
    sprintf(msg, "%s %d", "[Barber] Starting to cut client ", pid);
    print_time(msg);

    sleep(2); // brubrubu

    memset(msg, '\0', 128);
    sprintf(msg, "%s %d", "[Barber] Finished cut of client ", pid);
    print_time(msg);
}


void server_down(mqd_t mqd) {

    msgctl(msgqid, IPC_RMID, NULL);
    exit(0);
}

int sem_w(const int *semid) {

    struct sembuf sb;

    sb.sem_num = 0;
    sb.sem_op = -1; //Allocate resources
    sb.sem_flg = 0;
    if (semop(*semid, &sb, 1) == -1)
        error_and_die("semop");
    return 1;

}

int sem_p(const int *semid) {

    struct sembuf sb;

    sb.sem_num = 0;
    sb.sem_op = 1; //Allocate resources
    sb.sem_flg = 0;
    if (semop(*semid, &sb, 1) == -1)
        error_and_die("semop");
    return 1;
}
