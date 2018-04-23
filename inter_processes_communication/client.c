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
#define MSGTXTLEN 128   // msg text length
#define MSGPERM 0600    // msg queue permission
#define MAX_BUF 1024
/* message buffer for msgsnd and msgrcv calls */
struct msgbuf {
    long mtype;         /* typ komunikatu  r */
    char mtext[MSGTXTLEN];      /* tresc komunikatu */
};

int main(){

    int fd;
    char * myfifo = "/tmp/myfifo";
    char buf[MAX_BUF];

    /* open, read, and display the message from the FIFO */
    fd = open(myfifo, O_RDONLY);
    read(fd, buf, MAX_BUF);
    printf("Received: %s\n", buf);

    struct msgbuf msg1;
    struct msgbuf msg2;

    msg1.mtype = 1;
    sprintf(msg1.mtext, "%s\n", "Hello!");

    msg2.mtype = 1;
    sprintf(msg2.mtext, "%s\n", "Go Go!");

    printf("sending msg: %s\n", msg1.mtext);
    printf("sending msg: %s\n", msg2.mtext);

    int msgqid =  (int) strtol(buf, NULL, 10);
    int rc = msgsnd(msgqid, &msg1, sizeof(msg1.mtext), 0);
    if (rc < 0) {
        perror(strerror(errno));
        printf("msgsnd failed, rc = %d\n", rc);
        return 1;
    }


    close(fd);


}