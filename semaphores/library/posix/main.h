//
// Created by radekkoziol on 05.05.18.
//

#ifndef SEMAPHORES_MAIN_H
#define SEMAPHORES_MAIN_H

#include <stdbool.h>

#define FIFO_NAME "/tmp/myfifao"
#define MAX_BUF 1024
#define MEMORY_NAME  "sample"
#define SERVER_NAME "/test_queue"
#define MAX_CLIENT_NO 32
#define MSG_SIZE 128
#define MAX_MSG 10

struct barbershop{
    int c_number;
    int c_max_number;
    bool is_sleeping;
    pid_t *client_id;
    sem_t b_s;
    sem_t c_s[MAX_CLIENT_NO];


};



#endif //SEMAPHORES_MAIN_H
