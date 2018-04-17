//
// Created by radekkoziol on 17.04.18.
//
#include <sys/stat.h>
#include <zconf.h>
#include <fcntl.h>
#include <stdio.h>
#include <bits/types/sig_atomic_t.h>
#include <memory.h>
#include <signal.h>
#include <stdlib.h>

#define MAX_BUF 1024
static volatile sig_atomic_t got_sigint_signal = 0;

void stop_program(int signum) {
    got_sigint_signal = 1;
}

int
main(int argc, char **argv) {

    //No really input control
    const char *path = argv[1];

    int fd;

    /* create the FIFO (named pipe) */
    mkfifo(path, 0666);

    // Setting handler for stopping
    struct sigaction action, sa;

    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_handler = &stop_program;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return EXIT_FAILURE;
    }

    sigaction(SIGINT, NULL, &action);


    while (1) {

        char buf[MAX_BUF];
        for (int i = 0; i < MAX_BUF; i++)
            buf[i] = '\0';

        /* open, read, and display the message from the FIFO */
        fd = open(path, O_RDONLY);

        if (read(fd, buf, MAX_BUF))
            printf("Received:\n%s", buf);
        else { // if nothing comes
            printf("\nUnable to read more!. Exiting program\n");
            exit(0);
        }

        if (got_sigint_signal) {
            printf("\nReceived STOP signal. Exiting!\n");

            close(fd);
            /* remove the FIFO */
            unlink(path);
            exit(0);
        }

    }

}