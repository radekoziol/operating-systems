//
// Created by radekkoziol on 27.05.18.
//


#include <stdio.h>
#include <zconf.h>
#include <stdlib.h>
#include <memory.h>
#include <semaphore.h>
#include <bits/signum.h>
#include <signal.h>
#include "../main.h"

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

int read_counter(char o) {

    int p = -1;

    if (o == 'c') {
        sem_wait(&cl_c);
        p = cl_counter % buf_size;
        cl_counter++;
        sem_post(&cl_c);
    } else if (o == 'p') {
        sem_wait(&pr_c);
        p = pr_counter % buf_size;
        pr_counter++;
        sem_post(&pr_c);
    }

    return p;
}

void free_space() {
    for (int i = 0; i < buf_size; i++) {
        for (int j = 0; j < 3; j++)
            sem_destroy(&sem[i][j]);
    }
    sem_destroy(&cl_c);
    sem_destroy(&pr_c);
    sem_destroy(&line_sem);

    free(sem);

    fclose(file);
}

bool cl_wait() {
    return buffer[last_buf - 1] == NULL;
}

void force_stop() {

    printf("[Main] Waiting for clients to read rest\n");
    while (!cl_wait());

    printf("[Main] Killing threads\n");
    for (int i = 0; i < p_num; i++) {
        if (pthread_cancel(prod_id[i]) != 0)
            error_and_die("pthread_create");
    }
    for (int i = 0; i < c_num; i++) {
        if (pthread_cancel(cl_id[i]) != 0)
            error_and_die("pthread_create");
    }

    free_space();
}

void controller(int t) {

    // Blocking SIGINT
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    pthread_sigmask(SIG_BLOCK, &set, NULL);

    if (t != 0) {
        sleep((unsigned int) t);
        force_stop();
    }

}

void initialize_arg(int argc, char *argv[]) {

    if (argc < 7 || (strcmp(argv[1], "-help") == 0)) {
        printf("Arguments to program are:\n"
               "<p_num> <c_num> <buf_size> <fix_len> <comparator> <print> <max_time>");
        exit(0);
    }

    char buf[256];
    memset(buf, '\0', sizeof(buf));
    sprintf(buf, "%s %s %s %s %s %s %s", argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);

    comp = '\0';
    char print = '\0';
    if (sscanf(buf, "%d %d %d %d %c %c %d",
               &p_num, &c_num, &buf_size, &fix_len, &comp, &print, &max_time) != 7) {
        printf("Wrong arguments format!\n");
        exit(-1);
    }

    if (print == 't') print_more_info = true;

    printf("[Main] Creating %d clients, %d producers, buffer of size %d, "
           "fix_len = %d, comp = %c, print = %c\n",
           c_num, p_num, buf_size, fix_len, comp, print);

    sem_init(&line_sem, 0, 1);
    sem_init(&cl_c, 0, 1);
    sem_init(&pr_c, 0, 1);

    sem = (sem_t **) malloc((size_t) buf_size * sizeof(sem_t *));
    for (int i = 0; i < buf_size; i++) {
        sem[i] = (sem_t *) malloc(3 * sizeof(sem_t));
    }

    for (int i = 0; i < buf_size; i++) {
        for (int j = 0; j < 3; j++) {
            if (j == 0)
                sem_init(&sem[i][j], 0, 1);
            else
                sem_init(&sem[i][j], 0, 0);
        }
    }

    struct sigaction action, sa;

    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_handler = (__sighandler_t) &force_stop;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    file = fopen("../pan-tadeusz.txt", "r");
    if (file == NULL)
        error_and_die("open : unable to open text!\n");

    memset(buf, '\0', sizeof(buf));

}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

void append_text(int p) {

    sem_wait(&line_sem);

    char line[1024];
    memset(line, '\0', sizeof(line));

    if (file && fgets(line, 1024, file) != NULL) {
        buffer[p] = calloc(strlen(line) + 1, sizeof(char));
        strcpy(buffer[p], line);
    } else {
        printf("*** End of file ***\n");
        last_buf = p;
        kill(getpid(), SIGINT);
        sem_wait(&line_sem);
    }

    sem_post(&line_sem);
}

void producer() {

    int p = read_counter('p');

    // Ignoring SIGINT
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    pthread_sigmask(SIG_BLOCK, &set, NULL);

    while (1) {

        // Lock
        sem_wait(&sem[p][0]);

        if (print_more_info && printf("[Producer %lu] Adding to %d!\n", pthread_self(), p)) {}

        if (buffer[p] != NULL) {
            sem_post(&sem[p][0]);
            printf("[Producer %lu] Waiting for client to read!\n", pthread_self());
            sem_wait(&sem[p][2]);
        } else {

            append_text(p);

            if (print_more_info && printf("[Producer %lu] Done!\n", pthread_self())) {}

            // Unlock
            sem_post(&sem[p][0]);

            // Notify
            int value;
            sem_getvalue(&sem[p][1], &value);
            if (value == 0) {
                sem_post(&sem[p][1]);
            }

            p = read_counter('p');

        }

    }


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
    printf("[Client %lu] Read \n%s", pthread_self(), string);
}

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-noreturn"

void client() {

    int p = read_counter('c');

    // Blocking SIGINT
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    pthread_sigmask(SIG_BLOCK, &set, NULL);

    while (1) {

        if (print_more_info && printf("[Client %lu] Trying to read from %d!\n", pthread_self(), p)) {}

        sem_wait(&sem[p][0]);

        if (buffer[p] != NULL) {

            read_string(buffer[p]);

            if (print_more_info && printf("[Client %lu] Freeing memory!\n", pthread_self())) {}

            free(buffer[p]);
            buffer[p] = NULL;

            sem_post(&sem[p][0]);

            // Notify
            int value = 1;
            sem_getvalue(&sem[p][2], &value);
            if (value == 0)
                sem_post(&sem[p][2]);

            p = read_counter('c');

        } else {
            if (print_more_info && printf("[Client %lu] Nothing is there!\n", pthread_self()));
            sem_post(&sem[p][0]);
            int val;
            sem_getvalue(&sem[p][1], &val);
            if (print_more_info && printf("[Client %lu] Waiting on %d!\n", pthread_self(), p));
            sem_wait(&sem[p][1]);
        }


    }


}

