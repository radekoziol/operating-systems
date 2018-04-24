//
// Created by radekkoziol on 24.04.18.
//


#include <stdlib.h>
#include <stdbool.h>
#include <zconf.h>
#include <stdio.h>
#include <time.h>
#include <memory.h>
#include <signal.h>

bool starts_with(char string[4], char *msg);

void calculate_arth_expr(char *msg);

void get_current_time(char *msg);

int extract_id(const char mtext[128]) {

    int it = 0;
    char id[32];
    while (mtext[it] != ':') {
        id[it] = mtext[it];
        it++;
    }
    id[it] = '\0';

    return (int) strtol(id, NULL, 10);
}

void parse_to_operation(char mtext[128]){
    int it = 0;
    while (mtext[it] != ':')
        it++;

    it++;
    int c = 0;
    while(mtext[it] != '\0')
        mtext[c++] = mtext[it++];
    mtext[c] = '\0';

}
// reverse the given null-terminated string in place
void inplace_reverse(char * str)
{
    if (str)
    {
        char * end = str + strlen(str) - 1;

        // swap the values in the two given variables
        // XXX: fails when a and b refer to same memory location
#   define XOR_SWAP(a,b) do\
    {\
      (a) ^= (b);\
      (b) ^= (a);\
      (a) ^= (b);\
    } while (0)

        // walk inwards from both ends of the string,
        // swapping until we get to the middle
        while (str < end)
        {
            XOR_SWAP(*str, *end);
            str++;
            end--;
        }
#   undef XOR_SWAP
    }
}

void calculate(char msg[128], long operation) {

    switch(operation) {
        // Mirror
        case 2 :
            inplace_reverse(msg);
        // Calc
        case 3 :
            calculate_arth_expr(msg);
        // Time
        case 4 :
            get_current_time(msg);

        default:break;
    }

}

void get_current_time(char *msg) {
    time_t rawtime;
    struct tm * timeinfo;

    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    sprintf(msg,"%s",asctime(timeinfo));
}

void calculate_arth_expr(char *msg) {

    char x[64];
    char y[64];
    char operation;

    int it = 0;

    while(it<64 && msg[it] >= 38 && msg[it] <= 57){
        x[it] = msg[it];
        it++;
    }
    x[it] = '\0';

    operation = msg[it++];

    int it1 = 0;
    while(it<128 && it1<64 && msg[it] >= 38 && msg[it] <= 57){
        y[it1] = msg[it];
        it1++; it++;
    }
    y[it1] = '\0';

    int z1 = (int) strtol(x,NULL,10);
    int z2 = (int) strtol(y,NULL,10);


    switch(operation) {
        case '+' : z1 += z2;
        case '-' : z1 -= z2;
        case '*' : z1 *= z2;
        case '/' : if(z2 != 0) z1 /= z2; else z2 = -1;
        default:break;
    }

    sprintf(msg,"%d",z1);

}

bool in_id_format(const char mtext[128]) {
    int it = 0;
    while (mtext[it] != '\0') {
        if (!(mtext[it] >= 38 && mtext[it] <= 57))
            return false;
        it++;
    }
    return true;
}

bool in_operation_format(const char mtext[128]) {

    int it = 0;
    char id[128];
    while (mtext[it] != '\0' && mtext[it] != ':' && it < 128) {
        id[it] = mtext[it];
        it++;
    }

    if (mtext[it] == ':') {
        id[it] = '\0';
        if (!in_id_format(id))
            return false;
    }

    return true;
}

