//
// Created by radekkoziol on 17.04.18.
//

#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <memory.h>
#include <errno.h>
#include <mqueue.h>
#include <sys/stat.h>        /* For mode constants */
#include <zconf.h>
#include <bits/types/sig_atomic_t.h>
#include <signal.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utils.c"

#define MSGTXTLEN 128   // msg text length
#define MSGPERM 0600    // msg queue permission

static volatile sig_atomic_t got_sigint_signal = 0;

int id = 0;
int msgqid, rc;
int client_id[MSGTXTLEN];

/* message buffer for msgsnd and msgrcv calls */
struct msgbuf {
    long mtype;         /* typ komunikatu  r */
    char mtext[MSGTXTLEN];      /* tresc komunikatu */
};
        // swap the values in the two given variables

void stop_program(int signum) {
    got_sigint_signal = 1;
}

int main() {

    // Setting handler for stopping
    struct sigaction action, sa;

    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_handler = &stop_program;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return EXIT_FAILURE;
    }

    sigaction(SIGINT, NULL, &action);

    /*
    create a message queue. If here you get a invalid msgid and use it in msgsnd() or msgrcg(),
    an Invalid Argument error will be returned.
    */
    msgqid = msgget(IPC_PRIVATE, MSGPERM | IPC_CREAT | IPC_EXCL);
    if (msgqid < 0) {
        perror(strerror(errno));
        printf("failed to create message queue with msgqid = %d\n", msgqid);
        return 1;
    }

    // Sharing server id
    int fd;
    char *myfifo = "/tmp/fifo";
    /* create the FIFO (named pipe) */
    mkfifo(myfifo, 0666);


    while (1) {


        // Sharing id
        fd = open(myfifo, O_WRONLY);
        char buf[1024];
        sprintf(buf, "%d ", msgqid);
        write(fd, buf, sizeof(buf));

        // Exiting program - closing pipes etc.
        if (got_sigint_signal) {
            printf("\nExiting\n");
            close(fd);
            /* remove the FIFO */
            unlink(myfifo);

            msgctl(msgqid, IPC_RMID, NULL);
            exit(0);
        }


        struct msgbuf msg;
        if (msgrcv(msgqid, &msg, 1024, 0, 0)) {

            // Saving id of client before fork
            if (msg.mtype == 1) {
                printf("Received message: %s\n", msg.mtext);
                client_id[id] = (int) strtol(msg.mtext, NULL, 10);
            }
            if (fork() == 0) {
                if ((msg.mtype == 1) && (in_id_format(msg.mtext))) {
                    printf("Sending identifier %d\n", id);

                    msg.mtype = 1;
                    sprintf(msg.mtext, "%d", id);
                    rc = msgsnd(client_id[id], &msg, sizeof(msg.mtext), 0);
                    if (rc < 0) {
                        perror(strerror(errno));
                        printf("msgsnd failed, rc = %d\n", rc);
                        return 1;
                    }
                } else if ((msg.mtype > 1) && msg.mtype <= 4 && (in_operation_format(msg.mtext))) {
                    printf("Received operation request %s\n", msg.mtext);

                    int input_id = extract_id(msg.mtext);
                    parse_to_operation(msg.mtext);

                    printf("Sending back to %d!\n", client_id[input_id]);

                    if (input_id == -1) {
                        sprintf(msg.mtext, "%s\n", "Wrong format of request!\n");
                        rc = msgsnd(client_id[id], &msg, sizeof(msg.mtext), 0);
                    } else {
                        if (client_id[input_id] != -1) {
                            printf("Starting calculation!\n");
                            calculate(msg.mtext,msg.mtype);
                            printf("Sending back results!\n");
                            rc = msgsnd(client_id[input_id], &msg, sizeof(msg.mtext), 0);
                        } else {
                            sprintf(msg.mtext, "%s\n", "No queue to send results to!\n");
                            rc = msgsnd(client_id[input_id], &msg, sizeof(msg.mtext), 0);
                        }
                    }
                } else if (msg.mtype == 5){
                    printf("Ending program!\n");
                    kill(getppid(),SIGINT);
                }

                // Killing child
                _exit(EXIT_SUCCESS);

            } else {
                // Increase id counter
                if (msg.mtype == 1)
                    id++;

            }
        }


    }


}

