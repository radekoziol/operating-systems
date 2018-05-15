//
// Created by radekkoziol on 17.04.18.
//

#include <mqueue.h>

#include <stdlib.h>
#include <time.h>
#include "utils.c"
#include  <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>



int main() {

    struct barbershop *barber_s;
    /* measure monotonic time */
    clock_gettime(CLOCK_MONOTONIC_RAW, &start);    /* mark start time */

    int N = 5;
    key_t s_key, b_sem;
    int shm_id;


    // Get shared memory
    if ((s_key = ftok(SHARED_MEMORY_KEY, PROJECT_ID)) == -1)
        error_and_die("ftok");
    if ((shm_id = shmget(s_key, sizeof(struct barbershop),
                         0666 | IPC_CREAT)) == -1)
        error_and_die("shmget");
    if ((barber_s = (struct barbershop *) shmat(shm_id, NULL, 0))
        == (struct barbershop *) -1)
        error_and_die("shmat");


    barber_s->c_number = 0;
    barber_s->is_sleeping = false;
    barber_s->c_max_number = N;
    barber_s->mqd = server_up();

    if ((b_sem = ftok(SHARED_MEMORY_KEY, PROJECT_ID)) == -1)
        error_and_die("ftok");

    // semaphores init
    if ((barber_s->b_s = semget(b_sem, 1, 0660 | IPC_CREAT) < 0))
        error_and_die("semget");
    if ((semctl(barber_s->b_s, 0, SETVAL, 0)) < 0)
        error_and_die("semctl");

    for (int i = 0; i < MAX_CLIENT_NO; i++) {
        if ((barber_s->c_s[i] = semget(1241, 1, 0660 | IPC_CREAT) < 0))
            error_and_die("semget");

        argument.val = 0;
        if ((semctl(barber_s->c_s[i], 0, SETVAL, argument)) < 0)
            error_and_die("semctl");
    }


    barber_s->client_id = (pid_t *) malloc(MAX_CLIENT_NO * sizeof(pid_t));


    while (1) {

//        // Updating current cl num
        struct msqid_ds buf;

        if ((msgctl(barber_s->mqd, IPC_STAT, &buf)) < 0)
            error_and_die("msgctl");
        barber_s->c_number = (int) buf.msg_qnum;

//        // Exiting program
        if (got_sigint_signal) {

            printf("\nExiting\n");
            server_down(barber_s->mqd);

            exit(EXIT_SUCCESS);
        }

        if (barber_s->c_number == 0) {

            barber_s->is_sleeping = true;
            print_time("[Barber] Going to sleep");
            sem_w(&barber_s->b_s);

            if (!got_sigint_signal) {
                msg.mtype = 1;
                if (msgrcv(barber_s->mqd, &msg, sizeof(msg.mtext), 0, 0) >= 0) {
                    print_time("[Barber] Somebody woke me up!");
                    barber_s->is_sleeping = false;

                    pid_t pid;
                    if ((pid = (pid_t) strtol(msg.mtext, NULL, 10)) < 0) {
                        print_time("[Barber] Wrong pid format!");
                        print_time(NULL);
                    } else {
                        barber_s->is_sleeping = false;
                        cut_client(pid);
                        sem_p(&barber_s->c_s[pid % MAX_CLIENT_NO]);
                    }
                }
            }
        } else {
            struct msgbuf msg;
            msg.mtype = 0;
            if (msgrcv(barber_s->mqd, &msg, sizeof(msg), 0, 0) >= 0) {

                pid_t pid;
                if ((pid = (pid_t) strtol(msg.mtext, NULL, 10)) < 0) {
                    print_time("[Barber] Wrong pid format!");
                    print_time(NULL);
                } else {
                    cut_client(pid);
                    sem_p(&barber_s->c_s[pid % MAX_CLIENT_NO]);
                }
            }


        }

    }


}











