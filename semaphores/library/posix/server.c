//
// Created by radekkoziol on 17.04.18.
//

#include <mqueue.h>

#include <stdio.h>
#include <memory.h>
#include <bits/types/sig_atomic_t.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <zconf.h>
#include "utils.c"
#include "main.h"

mqd_t mqd;
static volatile sig_atomic_t got_sigint_signal = 0;


void cut_client(pid_t pid) {

    printf("[Barber] Starting to cut client %d\n", pid);
    //            print_time();
    sleep(2);
    printf("[Barber] Finished cut of client %d\n", pid);
    //            print_time();
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

void server_down(mqd_t mqd) {
    /* cleanup */
    mq_unlink(SERVER_NAME);
    mq_close(mqd);
    exit(0);
}


void intialize_shop(struct barbershop *b_shop) {

    struct barbershop shop;

    mqd = server_up();

    pid_t *pid_ar = (pid_t *) malloc(MAX_CLIENT_NO * sizeof(pid_t));
    shop.client_id = pid_ar;


    shop.c_number = 0;
    shop.is_sleeping = false;

    b_shop = &shop;
}

int main() {

    int N = 5;

    int r1;

    int fd = shm_open(MEMORY_NAME, O_CREAT | O_TRUNC | O_RDWR, 0666);
    if (fd == -1)
        error_and_die("shm_open");

    r1 = ftruncate(fd, sizeof(struct barbershop));
    if (r1 != 0)
        error_and_die("ftruncate");

    struct barbershop *barber_s = mmap(0, sizeof(struct barbershop), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (barber_s == MAP_FAILED)
        error_and_die("mmap");
    close(fd);

    mqd = server_up();


    barber_s->client_id = (pid_t *) malloc(MAX_CLIENT_NO * sizeof(pid_t));
    barber_s->b_s = *sem_open("barber_sem",O_CREAT, 0666, 0);
    for(int i =0; i<MAX_CLIENT_NO; i++){
        char num[2];
        memset(num,'\0',2);
        sprintf(num,"%d",i);
        char name[64];
        strcat(name,num);
        barber_s->c_s[i] = *sem_open(name,O_CREAT, 0666, 0);
    }


    barber_s->c_number = 0;
    barber_s->is_sleeping = false;
    barber_s->c_max_number = N;


    char msg[MSG_SIZE];
    while (1) {

        struct mq_attr attr;
        mq_getattr(mqd, &attr);
        barber_s->c_number = (int) attr.mq_curmsgs;

        // Exiting program
        if (got_sigint_signal) {

            printf("\nExiting\n");
            server_down(mqd);

            r1 = munmap(barber_s, sizeof(struct barbershop));
            if (r1 != 0)
                error_and_die("munmap");

            r1 = shm_unlink(MEMORY_NAME);
            if (r1 != 0)
                error_and_die("shm_unlink");

            exit(EXIT_SUCCESS);
        }

        if (barber_s->c_number == 0) {
            barber_s->is_sleeping = true;
            printf("[Barber] Going to sleep\n");
//            print_time();
            sem_wait(&barber_s->b_s);

            if(got_sigint_signal){
                memset(msg, '\0', 1024);
                if (mq_receive(mqd, msg, sizeof(msg), NULL) >= 0) {
                    printf("[Barber] Somebody woke me up!\n");
                    barber_s->is_sleeping = false;
                    printf("[Barber] Received message %s\n", msg);

                    pid_t pid;
                    if ((pid = (pid_t) strtol(msg, NULL, 10)) < 0) {
                        printf("[Barber] Wrong pid format! \n");
                        //            print_time();
                    } else {
                        barber_s->is_sleeping = false;
                        //            print_time();
                        cut_client(pid);
                        sem_post(&barber_s->c_s[pid % MAX_CLIENT_NO]);
                    }
                }
            }
        } else {
            memset(msg, '\0', 1024);
            if (mq_receive(mqd, msg, sizeof(msg), NULL) >= 0) {

                pid_t pid;
                if ((pid = (pid_t) strtol(msg, NULL, 10)) < 0) {
                    printf("[Barber] Wrong pid format! \n");
                    //            print_time();
                } else {
                    cut_client(pid);
                    sem_post(&barber_s->c_s[pid % MAX_CLIENT_NO]);
                }
            }


        }
    }


}











