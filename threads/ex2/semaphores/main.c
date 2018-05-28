

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#include "main.h"
#include "utils.c"


void initialize_sem(unsigned int C, unsigned int P) {

    sem_init(&cl_c,0,1);
    sem_init(&pr_c,0,1);

    sem = (sem_t**) malloc((size_t) max(C, P) * sizeof(sem_t*));
    for (int i = 0; i < max(C, P); i++) {
        for (int j = 0; j < 2; j++) {
            sem[i] = (sem_t*) malloc(2 * sizeof(sem_t*));
        }
    }
    for (int i = 0; i < max(C, P); i++) {
        for (int j = 0; j < 2; j++) {
            sem_init(&sem[i][j], 0, 1);
        }
    }

}

int main(void) {

    unsigned int N, P, C, L;

    N = 128;
    P = 2;
    C = 2;


    initialize_sem(C, P);

    pthreads_create(cl_id, C, client);
    pthreads_create(prod_id, P, producer);


    pthreads_wait(prod_id, P);
    pthreads_wait(cl_id, C);


    for (int i = 0; i < max(C, P); i++) {
        for (int j = 0; j < 2; j++)
            sem_close(&sem[i][j]);
    }

    free(sem);


    return 0;
}