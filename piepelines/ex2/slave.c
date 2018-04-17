//
// Created by radekkoziol on 17.04.18.
//

#include <zconf.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#define MAX_BUF 1024

int
main(int argc, char **argv) {
    argv[1] = "pipe";
    argv[2] = "10";
    const char * path = argv[1];
    const int N = (int) strtol(argv[2], NULL, 10);

    int fd;
    char * myfifo = "/tmp/myfifo";


    /* write "Hi" to the FIFO */
    fd = open(myfifo, O_WRONLY);
    dup2(fd,STDOUT_FILENO);
    printf("test\n");
    close(fd);

    
    return 0;

}