//
// Created by radekkoziol on 05.05.18.
//

#ifndef SEMAPHORES_MAIN_H
#define SEMAPHORES_MAIN_H

#include <stdbool.h>

#define FIFO_NAME "/tmp/myfifao"
#define MAX_BUF 1024
#define PROJECT_ID 'K'
#define SHARED_MEMORY_KEY "."
#define SERVER_NAME "/test_queue"
#define MAX_CLIENT_NO 28
#define MSG_SIZE 128
#define MAX_MSG 10
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>


struct timespec start, end;
static volatile sig_atomic_t got_sigint_signal = 0;

struct sembuf post_s = {0, 1, 0};
struct sembuf wait_s = {0, -1, 0};
union semun {
    int val;
    struct semid_ds *buf;
    ushort * array;
} argument;


struct msgbuf {
    long mtype;         /* typ komunikatu  r */
    char mtext[32];      /* tresc komunikatu */
}msg ;

struct barbershop {
    mqd_t mqd;
    int c_number;
    int c_max_number;
    bool is_sleeping;
    pid_t *client_id;
    // Semaphores
    int b_s;
    int c_s[28];

};


#endif //SEMAPHORES_MAIN_H
