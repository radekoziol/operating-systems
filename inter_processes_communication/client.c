//
// Created by radekkoziol on 20.04.18.
//

#include <sys/stat.h>
#include <fcntl.h>
#include <zconf.h>
#include <stdio.h>
#include <sys/msg.h>
#include <memory.h>
#include <stdlib.h>
#include <errno.h>
#include "utils.c"

#define MSGTXTLEN 128   // msg text length
#define MSGPERM 0600    // msg queue permission
#define MAX_BUF 1024

/* message buffer for msgsnd and msgrcv calls */
struct msgbuf {
    long mtype;         /* typ komunikatu  r */
    char mtext[MSGTXTLEN];      /* tresc komunikatu */
};

int main() {

    int fd;
    char *myfifo = "/tmp/fifo";
    char buf[MAX_BUF];

    /* open, read, and display the message from the FIFO */
    fd = open(myfifo, O_RDONLY);
    if (read(fd, buf, MAX_BUF))
        printf("Received: %s\n", buf);
    int server_id = (int) strtol(buf, NULL, 10);

    // Creating private queue
    int client_id = msgget(IPC_PRIVATE, MSGPERM | IPC_CREAT | IPC_EXCL);

    if (client_id < 0) {
        perror(strerror(errno));
        printf("failed to create message queue with msgqid = %d\n", client_id);
        return 1;
    }

    struct msgbuf msg1;
    struct msgbuf msg2;

    msg1.mtype = 1;
    sprintf(msg1.mtext, "%d", client_id);

    printf("sending msg: %s\n", msg1.mtext);

    int rc = msgsnd(server_id, &msg1, sizeof(msg1.mtext), 0);

    if (rc < 0) {
        perror(strerror(errno));
        printf("msgsnd failed, rc = %d\n", rc);
        return 1;
    }


    if (msgrcv(client_id, &msg2, 1024, 0, 0)) {

        printf("Received from server %s\n", msg2.mtext);
        close(fd);
    }
    int id = (int) strtol(msg2.mtext,NULL,10);

    struct msgbuf msg3;
    struct msgbuf msg4;

    msg3.mtype = 3;
    sprintf(msg3.mtext, "%d:%s", id, "2*2");

    printf("sending msg: %s\n", msg3.mtext);

    rc = msgsnd(server_id, &msg3, sizeof(msg3.mtext), 0);

    if (rc < 0) {
        perror(strerror(errno));
        printf("msgsnd failed, rc = %d\n", rc);
        return 1;
    }

    if (msgrcv(client_id, &msg4, 1024, 0, 0)) {

        printf("Received from server %s\n", msg4.mtext);
        close(fd);
    }



    msgctl(client_id, IPC_RMID, NULL);
}