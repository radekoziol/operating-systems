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

    int cl_num = 5,visit_num = 3;

    int fd = shm_open(MEMORY_NAME, O_RDWR, 0);
    if (fd == -1)
        error_and_die("shm_open");

    void *barber = mmap(0, sizeof(struct barbershop), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (barber == MAP_FAILED)
        error_and_die("mmap");
    close(fd);


    struct barbershop *barber_s = barber;

    mqd = server_up();

    for (int i = 0; i < cl_num; i++) {

        if (fork() == 0) {

            for (int j = 0; j < visit_num; j++) {

                char msg[MSG_SIZE];

                memset(msg, '\0', MSG_SIZE);
                sprintf(msg, "%d", getpid());

                if (barber_s->is_sleeping) {
                    barber_s->is_sleeping = false;
                    printf("[Client %d] Waking up barber\n",getpid());
                    sem_post(&barber_s->b_s);
                    // print_time();
                    errno = mq_send(mqd, msg, strlen(msg), 1);
                    sem_wait(&barber_s->c_s[getpid() % MAX_CLIENT_NO]);
                    printf("[Client %d] Leaving barbershop!\n",getpid());
                    // print_time();
                } else if (barber_s->c_number < barber_s->c_max_number) {
                    errno = mq_send(mqd, msg, strlen(msg), 1);
                    if (errno != EAGAIN) {
                        barber_s->c_number++;
                        printf("[Client %d] Added to queue successfully!\n",getpid());
                        // print_time();
                        sem_wait(&barber_s->c_s[getpid() % MAX_CLIENT_NO]);
                        printf("[Client %d] Leaving barbershop!\n",getpid());
                        barber_s->c_number--;
                        // print_time();
                    }
                } else if (barber_s->c_number >= barber_s->c_max_number){
                    printf("[BARBER SHOP] Can not add more clients\n");
                    //print_time();
                }

            }

            exit(EXIT_SUCCESS);

        }


    }

    pid_t child_pid, wpid;
    int status = 0;

    while ((wpid = wait(&status)) > 0); // this way, the father waits for all the child processes



}
