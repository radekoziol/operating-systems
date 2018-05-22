

#include <stdio.h>
#include <pthread.h>
#include <zconf.h>
#include <stdlib.h>
#include <asm/errno.h>

pthread_t thread_id[1024];


int x, y;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//pthread_cond_t cond   = PTHREAD_COND_INITIALIZER;
//pthread_mutex_t x_mutex = PTHREAD_MUTEX_INITIALIZER;


void error_and_die(char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}


void pthreads_create(int num, void *fun) {

    pthread_attr_t attr;
    pthread_attr_init(&attr);

    

    for (int i = 0; i < num; i++) {
        if (pthread_create(&thread_id[i], NULL, fun, NULL) != 0)
            error_and_die("pthread_create");
    }
}

void pthreads_wait(int num) {
    // wait
    for (int i = 0; i < num; i++)
        pthread_join(thread_id[i], NULL);

}

void th_handler() {

    printf("[Thread %d] Trying to calculate! \n", (int) pthread_self());

    if (pthread_mutex_lock(&mutex) == EDEADLK) {
        printf("Unable to read from mutex!\n");
        _exit(-1);
    }

    if (pthread_self() < 0) {
        printf("Unable to read from mutex!\n");
        _exit(-1);
    }

    printf("[Thread %d] x = %d\n", (int) pthread_self(), x);

    sleep(1);
    x += 1;

    printf("[Thread %d] Done editing x = %d\n", (int) pthread_self(), x);


    if (pthread_mutex_unlock(&mutex) != 0) {
        printf("Unable to unlock mutex!\n");
        _exit(-1);
    }

    printf("[Thread %d] Unlocking!\n", (int) pthread_self());

}


int main(void) {


    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);

    pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_ERRORCHECK);

    pthread_mutex_init(&mutex, &attr);

    int th_num = 10;

    pthreads_create(th_num, th_handler);

    pthreads_wait(th_num);

}