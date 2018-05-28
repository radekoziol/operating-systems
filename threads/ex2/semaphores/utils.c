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

void read_string(const char *string) {

    bool print = false;

    switch (comp) {
        case '>':
            print = strlen(string) > fix_len;
            break;
        case '<':
            print = strlen(string) < fix_len;
            break;
        default:
            print = strlen(string) == fix_len;
            break;
    }

//    if (print)
        printf("[Client %lu] Read %s\n", pthread_self(), string);
}

void client() {

    sem_wait(&cl_c);
    const int p = cl_counter % buf_size;
    cl_counter++;
    sem_post(&cl_c);

    while (1) {

        if (print_more_info && printf("[Client %lu] Trying to read from %d!\n", pthread_self(),p)) {}

        if (sem_wait(&sem[p][0]) == 0) {

            if (buffer[p] != NULL) {

                read_string(buffer[p]);

                if (print_more_info && printf("[Client %lu] Freeing memory!\n", pthread_self())) {}

                free(buffer[p]);

                sem_post(&sem[p][0]);
                is_cl_alive[p] = false;
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

void append_text(const int p) {

    sem_wait(&line_sem);
    int read_till = line_read;
    line_read++;
    sem_post(&line_sem);

    FILE *f = fopen("../example_text.txt", "r");
    if (f == NULL)
        error_and_die("fopen : unable to open text!\n");

    char line[256];
    memset(line, '\0', sizeof(line));

    int counter = 0;
    while (fgets(line, sizeof line, f) != NULL) {
        if (counter == read_till) {
            buffer[p] = malloc(strlen(line) * sizeof(char));
            strcpy(buffer[p], line);
            break;
        }
        counter++;
    }

    fclose(f);

}

void producer() {

    sem_wait(&pr_c);
    const int p = pr_counter % buf_size;
    pr_counter++;
    sem_post(&pr_c);

    while (1) {

        if (sem_wait(&sem[p][0]) == 0) {

            if (print_more_info && printf("[Producer %lu] Adding to %d!\n", pthread_self(),p)) {}

            append_text(p);

            if (print_more_info && printf("[Producer %lu] Done!\n", pthread_self())) {}

            int value = 1;
            if (sem_getvalue(&sem[p][1], &value) != 0)
                error_and_die("sem_getvalue : unable to read from sem");
            else if (value == 0)
                sem_post(&sem[p][1]);

            sem_post(&sem[p][0]);

            is_prod_alive[p] = false;
            pthread_exit(NULL);
        }
    }


}

