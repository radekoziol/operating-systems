//
// Created by radekkoziol on 17.04.18.
//

#include <mqueue.h>

#include <stdio.h>
#include <memory.h>
#include <bits/types/sig_atomic_t.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <zconf.h>
#include <time.h>
#include "utils.c"

mqd_t mqd;

int main(int argc, char **argv) {


//    Example input
//    argc = 1;
//    argv[1] = "5";

    if ((argc == 0) || strcmp(argv[1], "-help") == 0) {
        printf("Arguments are: \n"
               "   seats_num \n");
        exit(0);
    }

    int N = (int) strtol(argv[1], NULL, 10);

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

    clock_gettime(CLOCK_MONOTONIC_RAW, &barber_s->start);    /* mark start time */
    start_t = barber_s->start;

    mqd = server_up();

    barber_s->client_id = (pid_t *) malloc(MAX_CLIENT_NO * sizeof(pid_t));
    barber_s->b_s = *sem_open("barber_sem", O_CREAT, 0666, 0);

    for (int i = 0; i < MAX_CLIENT_NO; i++) {
        char num[2];
        memset(num, '\0', 2);
        sprintf(num, "%d", i);
        char name[64];
        strcat(name, num);
        barber_s->c_s[i] = *sem_open(name, O_CREAT, 0666, 0);
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
            print_time("[Barber] Going to sleep");
            sem_wait(&barber_s->b_s);

            if (!got_sigint_signal) {
                memset(msg, '\0', 1024);
                if (mq_receive(mqd, msg, sizeof(msg), NULL) >= 0) {
                    print_time("[Barber] Somebody woke me up!");
                    barber_s->is_sleeping = false;

                    pid_t pid;
                    if ((pid = (pid_t) strtol(msg, NULL, 10)) < 0) {
                        print_time("[Barber] Wrong pid format!");
                        print_time(NULL);
                    } else {
                        barber_s->is_sleeping = false;
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
                    print_time("[Barber] Wrong pid format!");
                    print_time(NULL);
                } else {
                    cut_client(pid);
                    sem_post(&barber_s->c_s[pid % MAX_CLIENT_NO]);
                }
            }


        }
    }


}











