//
// Created by radekkoziol on 06.06.18.
//

#include <stdio.h>
#include <stdlib.h>

void error_and_die(char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}
