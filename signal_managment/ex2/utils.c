//
// Created by radekkoziol on 09.04.18.
//

#include <zconf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

int get_random_signal() {
    return rand() % (SIGRTMAX - SIGRTMIN) + SIGRTMIN;
}


int work() {
    int t = rand() % 4 + 1;
    sleep((unsigned int) t);
    return t;
}
