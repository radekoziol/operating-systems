//
// Created by radekkoziol on 24.04.18.
//


#define MSGTXTLEN 128   // msg text length
#define MSGPERM 0600    // msg queue permission
#define MAX_BUF 1024

void error_and_die(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}
