//
// Created by radekkoziol on 24.04.18.
//


#include <stdlib.h>
#include <stdbool.h>
#include <zconf.h>
#include <stdio.h>
#include <time.h>
#include <memory.h>

#define MSGTXTLEN 128   // msg text length
#define MSGPERM 0600    // msg queue permission
#define MAX_BUF 1024

// reverse the given null-terminated string in place
void inplace_reverse(char *str) {
    if (str) {
        char *end = str + strlen(str) - 1;

        // swap the values in the two given variables
        // XXX: fails when a and b refer to same memory location
#   define XOR_SWAP(a, b) do\
    {\
      (a) ^= (b);\
      (b) ^= (a);\
      (a) ^= (b);\
    } while (0)

        // walk inwards from both ends of the string,
        // swapping until we get to the middle
        while (str < end) {
            XOR_SWAP(*str, *end);
            str++;
            end--;
        }
#   undef XOR_SWAP
    }
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
            break;
        case '-' :
            z1 -= z2;
            break;
        case '*' :
            z1 *= z2;
            break;
        case '/' :
            if (z2 != 0) z1 /= z2;
            else z2 = -1;
        default:
            break;
    }

    sprintf(msg, "%d", z1);

}

void get_current_time(char *msg) {
    printf("XD");
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    sprintf(msg, "%s", asctime(timeinfo));
}

void calculate(char *msg, long operation) {

    sleep(1);
    printf("op id: %li",operation);
    printf("op: %s",msg);

    switch (operation) {
        // Mirror
        case 2 :
            inplace_reverse(msg);
            break;
            // Calc
        case 3 :
            calculate_arth_expr(msg);
            break;
            // Time
        case 4 :
            get_current_time(msg);
            break;

        default:
            break;
    }

}

