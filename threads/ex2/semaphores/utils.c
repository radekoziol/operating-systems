//
// Created by radekkoziol on 27.05.18.
//


#include <stdio.h>
#include <zconf.h>
#include <stdlib.h>
#include <memory.h>
#include <semaphore.h>
#include "main.h"

int max(unsigned int c, unsigned int p) {
    return c > p ? c : p;
}

void error_and_die(char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void pthreads_create(pthread_t *id_ar, int num, void *fun) {

    pthread_attr_t attr;
    pthread_attr_init(&attr);


    for (int i = 0; i < num; i++) {
        if (pthread_create(&id_ar[i], NULL, fun, NULL) != 0)
            error_and_die("pthread_create");
    }
}

void pthreads_wait(pthread_t *id_ar, int num) {
    // wait
    for (int i = 0; i < num; i++)
        pthread_join(id_ar[i], NULL);

}

void client() {

    sem_wait(&cl_c);
    const int p = cl_counter;
    cl_counter++;
    sem_post(&cl_c);

    printf("[Client %lu] Trying to read!\n", pthread_self());
    while (1) {

        if (sem_wait(&sem[p][0]) == 0) {
            printf("[Client %lu] Reading\n", pthread_self());

            if (buffer[p] != NULL) {
                printf("[Client %lu] Read %s\n", pthread_self(), buffer[cl_counter - 1]);

                printf("[Client %lu] Freeing memory!\n", pthread_self());
                free(buffer[p]);

                sleep(1);
                printf("[Client %lu] Done!\n", pthread_self());

                sem_post(&sem[p][0]);
                pthread_exit(NULL);
            } else {
                printf("[Client %lu] Nothing is there!\n", pthread_self());
                sem_post(&sem[p][0]);
                printf("[Client %lu] Waiting!\n", pthread_self());
                sem_wait(&sem[p][1]);
            }
        }

    }


}

void producer() {


    sem_wait(&pr_c);
    const int p = pr_counter;
    pr_counter++;
    sem_post(&pr_c);

    printf("[Producer %lu] Trying to add new product!\n", pthread_self());

    while (1) {

        if (sem_wait(&sem[p][0]) == 0) {

            printf("[Producer %lu] Adding!\n", pthread_self());

            char example_text[128] = "This is test!\n";
            buffer[p] = malloc(sizeof(example_text));
            strcpy(buffer[p], example_text);

            sleep(1);

            printf("[Producer %lu] Done!\n", pthread_self());

            int value = 1;
            if (sem_getvalue(&sem[p][1], &value) != 0)
                error_and_die("sem_getvalue : unable to read from sem");
            else if (value == 0)
                sem_post(&sem[p][1]);

            sem_post(&sem[p][0]);


            pthread_exit(NULL);
        }
    }


}

