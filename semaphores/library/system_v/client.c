//
// Created by radekkoziol on 20.04.18.
//

#include <fcntl.h>
#include <zconf.h>
#include <stdlib.h>

#include <mqueue.h>

#include <sys/shm.h>
#include <wait.h>
#include "utils.c"

mqd_t mqd;


int main() {

    int cl_num = 5, visit_num = 3;
    struct barbershop *barber_s;

    // Get shared memory
    int s_key, shm_id;

    if ((s_key = ftok(SHARED_MEMORY_KEY, PROJECT_ID)) == -1)
        error_and_die("ftok");
    if ((shm_id = shmget(s_key, sizeof(struct barbershop), 0)) == -1)
        error_and_die("shmget");
    if ((barber_s = (struct barbershop *) shmat(shm_id, NULL, 0))
        == (struct barbershop *) -1)
        error_and_die("shmat");


    for (int i = 0; i < cl_num; i++) {

        if (fork() == 0) {

            for (int j = 0; j < visit_num; j++) {

                struct msgbuf msg1;
                msg1.mtype = 1;
                memset(msg1.mtext, '\0', sizeof(msg1.mtext));
                sprintf(msg1.mtext, "%d", getpid());

                if (barber_s->is_sleeping) {

                    barber_s->is_sleeping = false;
                    printf("[Client %d] Waking up barber ", getpid());
                    print_time("");

                    sem_p(&barber_s->b_s);

                    if ((msgsnd(barber_s->mqd, &msg1, sizeof(msg1.mtext), 0) < 0))
                        error_and_die("msgsnd");

                    sem_w(&barber_s->c_s[getpid() % MAX_CLIENT_NO]);

                    printf("[Client %d] Leaving barbershop!", getpid());
                    print_time("");

                } else if (barber_s->c_number < barber_s->c_max_number) {

                    if (msgsnd(barber_s->mqd, &msg1, sizeof(msg1.mtext), 0) >= 0) {

                        barber_s->c_number++;
                        printf("[Client %d] Added to queue successfully!", getpid());
                        print_time("");

                        sem_w(&barber_s->c_s[getpid() % MAX_CLIENT_NO]);


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
