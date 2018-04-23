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
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <mqueue.h>
#include <zconf.h>
#include <string.h>
#include <bits/types/sig_atomic_t.h>
#include <signal.h>
#include <stdlib.h>

#define MSGTXTLEN 128   // msg text length
#define MSGPERM 0600    // msg queue permission

static volatile sig_atomic_t got_sigint_signal = 0;

int id = 0;
int msgqid, rc;

/* message buffer for msgsnd and msgrcv calls */
struct msgbuf {
    long mtype;         /* typ komunikatu  r */
    char mtext[MSGTXTLEN];      /* tresc komunikatu */
};

void stop_program(int signum) {
    got_sigint_signal = 1;
}

int main() {

    struct sigaction action,sa;

    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_handler = &stop_program;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return EXIT_FAILURE;
    }

    // Setting handler for stopping
    sigaction (SIGINT, NULL, &action);

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

    // No real input control
    const char *path = "tmp/fifo";

    int fd;
    char * myfifo = "/tmp/myfifo";

    /* create the FIFO (named pipe) */
    mkfifo(myfifo, 0666);



    while(1){

        fd = open(myfifo, O_WRONLY);
        char buf[1024];
        sprintf(buf,"%d ",msgqid);

        write(fd, buf, sizeof(buf));

        struct msgbuf msg3;

        if(msgrcv(msgqid, &msg3, 1024, 0, 0)){

            if(fork() == 0){

                printf("received msg: %s\n", msg3.mtext);
                printf("sending identifier: %d\n",id);

                int client_id = (int) strtol(msg3.mtext, NULL, 10);

                msg3.mtype = 1;
                sprintf(msg3.mtext, "%d", id);
                rc = msgsnd(client_id, &msg3, sizeof(msg3.mtext), 0);

                if (rc < 0) {
                    perror(strerror(errno));
                    printf("msgsnd failed, rc = %d\n", rc);
                    return 1;
                }


                sleep(5);
                printf("Work is done!\n");
                _exit(EXIT_SUCCESS);
            }else{
                id++;
                if(got_sigint_signal){
                    printf("\nExiting\n");
                    close(fd);
                    /* remove the FIFO */
                    unlink(path);

                    msgctl(msgqid, IPC_RMID, NULL);
                    exit(0);
                }
            }
        }





    }






}