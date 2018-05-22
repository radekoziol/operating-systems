#include "library.h"

#include <stdio.h>
#include <pthread.h>

int x,y;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond   = PTHREAD_COND_INITIALIZER;
pthread_mutex_t x_mutex = PTHREAD_MUTEX_INITIALIZER;

void th1(){

    pthread_mutex_lock(&mutex);
    while (x <= y) {
        pthread_cond_wait(&cond, &mutex);
    }


    pthread_mutex_unlock(&mutex);

}

void th2(){
    pthread_mutex_lock(&mutex);
/* zmiana x oraz y */
    if (x > y)
        pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);
}

void my_thread_safe_function() {
    /* Każdy dostęp do zmiennej x powinien się odbywać w następujący sposób: */
    pthread_mutex_lock(&x_mutex);

    /* operacje na x... */
    pthread_mutex_unlock(&x_mutex);
}


void hello(void) {
    printf("Hello, World!\n");
}