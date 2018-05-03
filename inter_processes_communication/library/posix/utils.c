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
