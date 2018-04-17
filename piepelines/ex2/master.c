#include <sys/stat.h>
#include <zconf.h>
#include <fcntl.h>
#include <fcntl.h>
#include <stdio.h>

#define MAX_BUF 1024

//
// Created by radekkoziol on 17.04.18.
//
int
main(int argc, char **argv) {
    argv[1] = "pipe";
    const char * path = argv[1];

    int fd;
    char * myfifo = "/tmp/myfifo";

    /* create the FIFO (named pipe) */
    mkfifo(myfifo, 0666);

    char buf[MAX_BUF];


    /* open, read, and display the message from the FIFO */
    fd = open(myfifo, O_RDONLY);
    read(fd, buf, MAX_BUF);
    printf("Received: %s\n", buf);
    close(fd);

    /* remove the FIFO */
    unlink(myfifo);

    return 0;

}