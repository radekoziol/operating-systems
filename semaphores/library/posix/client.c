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
#include "utils.c"
#include "main.h"

mqd_t mqd;

int server_up() {


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

int main() {

    int S = 5;

    int fd = shm_open(MEMORY_NAME, O_RDWR, 0);
    if (fd == -1)
        error_and_die("shm_open");

    void *barber = mmap(0, sizeof(struct barbershop), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (barber == MAP_FAILED)
        error_and_die("mmap");
    close(fd);


    struct barbershop *barber_s = barber;

    mqd = server_up();

    for (int i = 0; i < S; i++) {
        if (fork() == 0) {

            char msg[MSG_SIZE];

            memset(msg, '\0', MSG_SIZE);
            sprintf(msg, "%d", getpid());
            printf("c num %d, max c num %d\n", barber_s->c_number, barber_s->c_max_number);

            if (barber_s->c_number < barber_s->c_max_number) {

                if (barber_s->is_sleeping) {
                    sem_post(&barber_s->b_s);
                }

                if (mq_send(mqd, msg, strlen(msg), 1) >= 0) {
                    printf("[Client] Message send\n");
                    sem_wait(&barber_s->c_s[getpid() % MAX_CLIENT_NO]);

                } else {
                    perror("mq_open() error");
                    exit(-1);
                }



            } else {

                printf("[BARBER SHOP] Can not add more clients\n");
                //print_time();
                exit(EXIT_SUCCESS);

            }


            exit(EXIT_SUCCESS);
        }
    }


}
