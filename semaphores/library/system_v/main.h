//
// Created by radekkoziol on 05.05.18.
//

#ifndef SEMAPHORES_MAIN_H
#define SEMAPHORES_MAIN_H

#include <stdbool.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>

#define FIFO_NAME "/tmp/myfifao"
#define MAX_BUF 1024
#define PROJECT_ID 'K'
#define SHARED_MEMORY_KEY "."
#define SERVER_NAME "/test_queue"
#define MAX_CLIENT_NO 28
#define MSG_SIZE 128
#define MAX_MSG 10

static volatile sig_atomic_t got_sigint_signal = 0;

union semun {
    int val;
    struct semid_ds *buf;
    ushort *array;
} argument;


struct msgbuf {
    long mtype;
    char mtext[32];
};


struct barbershop {
    // For time measurement
    struct timespec start;
    // IPC
    mqd_t mqd;
    // Current client number and max client number
    int c_number, c_max_number;
    bool is_sleeping;
    // Array of clients pid
    pid_t *client_id;
    // Semaphores
    int b_s;
    // Limits due to
    // https://stackoverflow.com/questions/16630261/creating-my-first-unix-server-client-but-getting-a-shmget-invalid-argument-er
    int c_s[MAX_CLIENT_NO/2];
};


#endif //SEMAPHORES_MAIN_H
