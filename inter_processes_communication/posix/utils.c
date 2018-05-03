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

/* message buffer for msgsnd and msgrcv calls */
struct msgbuf {
    long mtype;         /* typ komunikatu  r */
    char mtext[MSGTXTLEN];      /* tresc komunikatu */
};

char *extract_name(const char mtext[128]) {

    int it = 0;

    while (mtext[it] != ':') it++;
    it++;

    char *name = calloc(128, sizeof(char));

    int c = 0;
    while (mtext[it] != '\0') {
        name[c] = mtext[it];
        it++;
        c++;
    }
    name[c] = '\0';

    return name;
}

int extract_type(const char mtext[128]) {

    return mtext[0] - '0';
}

void parse_to_operation(char mtext[128]) {

    int it = 0;
    while (mtext[it] != ':')
        it++;
    it++;
    while (mtext[it] != ':')
        it++;
    it++;
    while (mtext[it] != ':')
        it++;
    it++;

    int c = 0;
    while (mtext[it] != '\0')
        mtext[c++] = mtext[it++];
    mtext[c] = '\0';

}

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

// It should be number
bool in_id_format(const char mtext[128]) {
//    int it = 0;
//    while (mtext[it] != '\0') {
//        if (!(mtext[it] >= 48 && mtext[it] <= 57))
//            return false;
//        it++;
//    }
    return true;
}

// Fromat id:arguments, f.e 123123:4/2
bool in_operation_format(const char mtext[128]) {

//    int it = 0;
//    char id[128];
//    while (mtext[it] != '\0' && mtext[it] != ':' && it < 128) {
//        id[it] = mtext[it];
//        it++;
//    }
//
//    if (mtext[it] == ':') {
//        id[it] = '\0';
//
//        if (!in_id_format(id))
//            return false;
//    }

    return true;
}

char *generate_random_calculation_request(long id) {

    char *ar[5];
    for (int i = 0; i < 5; i++)
        ar[i] = (char *) malloc(32 * sizeof(char));

    sprintf(ar[2], "%d:%li:%d:%s", 2, id, 2, "mirror");
    sprintf(ar[3], "%d:%li:%d:%s", 2, id, 3, "23*3");
    sprintf(ar[4], "%d:%li:%d:%s", 2, id, 4, "whatev");

    time_t t;
    srand((unsigned) time(&t));

    return ar[rand() % 3 + 2];

}
