//
// Created by radekkoziol on 27.05.18.
//


#include <stdio.h>
#include <zconf.h>
#include <stdlib.h>
#include <memory.h>
#include <signal.h>
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
    printf("[Client %lu] Read\n%s", pthread_self(), string);
}

void append_text(const int p) {

    pthread_mutex_lock(&line_mut);

    char line[1024];
    memset(line, '\0', sizeof(line));

    if ((fgets(line, sizeof line, f)) != NULL) {
        buffer[p] = calloc(strlen(line), sizeof(char));
        strcpy(buffer[p], line);
    } else {
        kill(SIGINT, getpid());
    }

    pthread_mutex_unlock(&line_mut);

}

void client() {

    while (1) {

        pthread_mutex_lock(&cl_c);
        const int p = cl_counter % buf_size;
        cl_counter++;
        pthread_mutex_unlock(&cl_c);

        if (print_more_info && printf("[Client %lu] Trying to read from %d!\n", pthread_self(), p)) {}

        if (pthread_mutex_lock(&mutex[p]) == 0) {

            while (buffer[p] == NULL) {
                printf("[Client %lu] Nothing is there!\n", pthread_self());
                printf("[Client %lu] Waiting!\n", pthread_self());
                pthread_cond_wait(&cond[p][0], &mutex[p]);
            }
            sleep(1);

            read_string(buffer[p]);

            if (print_more_info && printf("[Client %lu] Freeing memory!\n", pthread_self())) {}
            free(buffer[p]);
            buffer[p] = NULL;

            pthread_cond_broadcast(&cond[p][1]);

            pthread_mutex_unlock(&mutex[p]);

        } else {
            pthread_exit(NULL);
        }

    }


}

void producer() {

    while (1) {

        pthread_mutex_lock(&pr_c);
        const int p = pr_counter % buf_size;
        pr_counter++;
        pthread_mutex_unlock(&pr_c);


        if (pthread_mutex_lock(&mutex[p]) == 0) {


            if (print_more_info && printf("[Producer %lu] Waiting to write to %d!\n", pthread_self(), p)) {}
            while (buffer[p] != NULL) {
                pthread_cond_wait(&cond[p][1], &mutex[p]);
            }

            if (print_more_info && printf("[Producer %lu] Adding to %d!\n", pthread_self(), p)) {}
            sleep(1);
            append_text(p);

            if (print_more_info && printf("[Producer %lu] Done!\n", pthread_self())) {}

            pthread_cond_broadcast(&cond[p][0]);

            pthread_mutex_unlock(&mutex[p]);

        } else {
            pthread_exit(NULL);
        }
    }


}

