//
// Created by radekkoziol on 06.06.18.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <strings.h>
#include <fcntl.h>
#include <memory.h>
#include <zconf.h>

void error_and_die(char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void calculate_arth_expr(char *msg) {

    char x[64];
    char y[64];
    char operation;

    int it = 0;

    while (it < 64 && msg[it] >= 48 && msg[it] <= 57) {
        x[it] = msg[it];
        it++;
    }
    x[it] = '\0';

    operation = msg[it++];

    int it1 = 0;
    while (it < 128 && it1 < 64 && msg[it] >= 38 && msg[it] <= 57) {
        y[it1] = msg[it];
        it1++;
        it++;
    }
    y[it1] = '\0';

    int z1 = (int) strtol(x, NULL, 10);
    int z2 = (int) strtol(y, NULL, 10);

    switch (operation) {
        case '+' :
            z1 += z2;
            sprintf(msg, "%d", z1);
            break;
        case '-' :
            z1 -= z2;
            sprintf(msg, "%d", z1);
            break;
        case '*' :
            z1 *= z2;
            sprintf(msg, "%d", z1);
            break;
        case '/' :
            if (z2 != 0) {
                float z3 = z1 / (float) z2;
                sprintf(msg, "%f", z3);
            } else {
                z2 = -1;
                sprintf(msg, "%d", z2);
            }
        default:
            break;
    }

}

void send_operation(int fd) {

    char operation[128];
    memset(operation,'\0',128);
    sprintf(operation,"%s","2*456");
//    printf("Please enter calculation: ");
//    fgets(operation, 128, stdin);
    printf("Trying to send!\n");

    if (send(fd, operation, sizeof(operation), 0) == -1){
        close(fd);
    }else{
        printf("Sent!\n");
    }


}

char* receive_response(int fd) {

    char *buffer = malloc(256);
    bzero(buffer, sizeof(buffer));
    recv(fd, buffer, 100, 0);

    return buffer;
}

void make_unblocking(int fd) {
    int flags, s;

    flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl");
        exit(-1);
    }

    flags |= O_NONBLOCK;
    s = fcntl(fd, F_SETFL, flags);
    if (s == -1) {
        perror("fcntl");
        exit(-1);
    }
}

