//
// Created by radekkoziol on 27.05.18.
//


#include <stdio.h>
#include <zconf.h>
#include <stdlib.h>
#include <memory.h>
#include <bits/sigthread.h>
#include <bits/signum.h>
#include <signal.h>
#include "../main.h"

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

void free_space() {

    for (int i = 0; i < max(c_num, p_num); i++) {
        pthread_mutex_destroy(&mutex[i]);
        for (int j = 0; j < 2; j++)
            pthread_cond_destroy(&cond[i][j]);
    }

    pthread_mutex_destroy(&cl_c);
    pthread_mutex_destroy(&pr_c);
    pthread_mutex_destroy(&line_mut);

    free(mutex);
    free(cond);

    fclose(f);

    exit(EXIT_SUCCESS);
}

bool cl_wait() {

    for(int i = 0; i < buf_size; i++)
        if(buffer[i] != NULL) return false;

    return true;

//    return buffer[last_buf - 1] == NULL;
}

void force_stop() {

    if(max_time != 0){
        printf("[Main] Waiting for clients to read rest\n");
        while (!cl_wait());
    }

    printf("[Main] Killing threads\n");
    for (int i = 0; i < p_num; i++) {
        if (pthread_cancel(prod_id[i]) != 0)
            error_and_die("pthread_cancel");
    }
    for (int i = 0; i < c_num; i++) {
        if (pthread_cancel(cl_id[i]) != 0)
            error_and_die("pthread_cancel");
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
               "<p_num> <c_num> <buf_size> <fix_len> <comparator> <print_more> <max_time>");
        exit(0);
    }

    char buf[256];
    memset(buf, '\0', sizeof(buf));
    sprintf(buf, "%s %s %s %s %s %s %s", argv[1], argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]);

    comp = '\0';
    char print[128];
    memset(print,'\0',128);
    if (sscanf(buf, "%d %d %d %d %c %s %d",
               &p_num, &c_num, &buf_size, &fix_len, &comp, print, &max_time) != 7) {
        printf("Wrong arguments format!\n");
        exit(-1);
    }

    if (strcmp(print, "true") == 0) print_more_info = true;

    printf("[Main] Creating %d clients, %d producers, buffer of size %d, "
           "fix_len = %d, comp = %c, print = %s\n",
           c_num, p_num, buf_size, fix_len, comp, print);

    pthread_mutex_init(&line_mut, NULL);
    pthread_mutex_init(&cl_c, NULL);
    pthread_mutex_init(&pr_c, NULL);

    mutex = (pthread_mutex_t *) malloc((size_t) buf_size * sizeof(pthread_mutex_t));
    cond = (pthread_cond_t **) malloc((size_t) buf_size * sizeof(pthread_cond_t *));
    for (int i = 0; i < buf_size; i++) {
        cond[i] = (pthread_cond_t *) malloc((size_t) 2 * sizeof(pthread_cond_t));
    }

    for (int i = 0; i < buf_size; i++) {
        for (int j = 0; j < 2; j++)
            cond[i] = (pthread_cond_t *) malloc((size_t) 2 * sizeof(pthread_cond_t));
    }

    for (int i = 0; i < buf_size; i++) {
        pthread_mutex_init(&mutex[i], NULL);
        for (int j = 0; j < 2; j++)
            pthread_cond_init(&cond[i][j], NULL);
    }

    struct sigaction action, sa;

    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_handler = (__sighandler_t) &force_stop;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Setting handler for stopping
    sigaction(SIGINT, NULL, &action);

    f = fopen("./pan-tadeusz.txt", "r");
    if (f == NULL)
        error_and_die("fopen : unable to open text!\n");

}

int read_counter(char o) {

    int p = -1;

    if (o == 'c') {
        pthread_mutex_lock(&cl_c);
        p = cl_counter % buf_size;
        cl_counter++;
        pthread_mutex_unlock(&cl_c);
    } else if (o == 'p') {
        pthread_mutex_lock(&pr_c);
        p = pr_counter % buf_size;
        pr_counter++;
        pthread_mutex_unlock(&pr_c);
    }

    return p;
}

bool check_string(const char *string) {

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

    return print;
}

void append_text(const int p) {

    pthread_mutex_lock(&line_mut);

    char line[1024];
    memset(line, '\0', sizeof(line));

    if (f && fgets(line, 1024, f) != NULL) {
        if (print_more_info && printf("[Producer %lu] Adding to %d!\n", pthread_self(), p)) {}
        buffer[p] = calloc(strlen(line) + 1, sizeof(char));
        strcpy(buffer[p], line);
    } else {
        printf("*** End of file ***\n");
        kill(getpid(), SIGINT);
        pthread_mutex_lock(&line_mut);
        return;
    }

    pthread_mutex_unlock(&line_mut);
}

void client() {

    pthread_detach(pthread_self());

    // Blocking SIGINT
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    pthread_sigmask(SIG_BLOCK, &set, NULL);

    int p = read_counter('c');

    while (1) {

        if (print_more_info && printf("[Client %lu] Trying to read from %d!\n", pthread_self(), p)) {}

        pthread_mutex_lock(&mutex[p]);

        while (buffer[p] == NULL) {
            if(print_more_info && printf("[Client %lu] Nothing is there! Waiting!\n", pthread_self()));
            pthread_cond_wait(&cond[p][0], &mutex[p]);
        }

        if(check_string(buffer[p]))
            printf("[Client %lu] Read\n%s", pthread_self(), buffer[p]);

        if (print_more_info && printf("[Client %lu] Freeing memory!\n", pthread_self()));
        free(buffer[p]);
        buffer[p] = NULL;

        pthread_cond_broadcast(&cond[p][1]);

        pthread_mutex_unlock(&mutex[p]);

        p = read_counter('c');

    }


}

void producer() {

    pthread_detach(pthread_self());

    // Blocking SIGINT
    sigset_t set;
    sigemptyset(&set);
    sigaddset(&set, SIGINT);
    pthread_sigmask(SIG_BLOCK, &set, NULL);

    int p = read_counter('p');

    while (1) {

        pthread_mutex_lock(&mutex[p]);

        while (buffer[p] != NULL) {
            if (print_more_info && printf("[Producer %lu] Waiting to write to %d!\n", pthread_self(), p)) {}
            pthread_cond_wait(&cond[p][1], &mutex[p]);
        }

        append_text(p);

        if (print_more_info && printf("[Producer %lu] Done!\n", pthread_self())) {}

        pthread_mutex_unlock(&mutex[p]);

        pthread_cond_broadcast(&cond[p][0]);

        p = read_counter('p');
    }

}
