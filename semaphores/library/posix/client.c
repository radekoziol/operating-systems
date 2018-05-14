//
// Created by radekkoziol on 20.04.18.
//

#include <fcntl.h>
#include <zconf.h>
#include <stdio.h>
#include <stdlib.h>

#include <mqueue.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <memory.h>
#include <errno.h>

#include <wait.h>
#include "utils.c"

mqd_t mqd;


int main() {

    int cl_num = 5, visit_num = 3;

    int fd = shm_open(MEMORY_NAME, O_RDWR, 0);
    if (fd == -1)
        error_and_die("shm_open");

    void *barber = mmap(0, sizeof(struct barbershop), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (barber == MAP_FAILED)
        error_and_die("mmap");
    close(fd);


    struct barbershop *barber_s = barber;

    mqd = server_open();

    for (int i = 0; i < cl_num; i++) {

        if (fork() == 0) {

            for (int j = 0; j < visit_num; j++) {

                char msg[MSG_SIZE];

                memset(msg, '\0', MSG_SIZE);
                sprintf(msg, "%d", getpid());

                if (barber_s->is_sleeping) {

                    barber_s->is_sleeping = false;
                    printf("[Client %d] Waking up barber ", getpid());
                    print_time("");

                    sem_post(&barber_s->b_s);

                    mq_send(mqd, msg, strlen(msg), 1);
                    sem_wait(&barber_s->c_s[getpid() % MAX_CLIENT_NO]);

                    printf("[Client %d] Leaving barbershop!", getpid());
                    print_time("");

                } else if (barber_s->c_number < barber_s->c_max_number) {

                    if (mq_send(mqd, msg, strlen(msg), 1) != EAGAIN) {

                        barber_s->c_number++;
                        printf("[Client %d] Added to queue successfully!", getpid());
                        print_time("");

                        sem_wait(&barber_s->c_s[getpid() % MAX_CLIENT_NO]);

                        printf("[Client %d] Leaving barbershop!", getpid());
                        print_time("");
                        barber_s->c_number--;
                    }
                } else if (barber_s->c_number >= barber_s->c_max_number) {
                    printf("[BARBER SHOP] Can not add more clients");
                    print_time("");
                }

            }

            exit(EXIT_SUCCESS);

        }


    }

    pid_t wpid;
    int status = 0;

    while ((wpid = wait(&status)) > 0); // this way, the father waits for all the child processes



}
