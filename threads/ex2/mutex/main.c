

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "main.h"
#include "utils.c"


void controller() {

    sleep(max_time);

    for (int i = 0; i < p_num; i++) {
        if (is_prod_alive[i])
            if (pthread_cancel(prod_id[i]) != 0)
                error_and_die("pthread_create");
    }
    for (int i = 0; i < c_num; i++) {
        if (is_cl_alive[i])
            if (pthread_cancel(cl_id[i]) != 0)
                error_and_die("pthread_create");
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

    pthread_mutex_init(&line_mut, NULL);
    pthread_mutex_init(&cl_c, NULL);
    pthread_mutex_init(&pr_c, NULL);

    mutex = (pthread_mutex_t *) malloc((size_t) buf_size * sizeof(pthread_mutex_t));
    cond = (pthread_cond_t **) malloc((size_t) buf_size * sizeof(pthread_cond_t *));
    for (int i = 0; i < 2; i++) {
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
    sa.sa_handler = &controller;

    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Setting handler for stopping
    sigaction(SIGINT, NULL, &action);

    f = fopen("../example_text.txt", "r");
    if (f == NULL)
        error_and_die("fopen : unable to open text!\n");

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

}


int main(int argc, char *argv[]) {

    // Example input
    argc = 7;
    argv[1] = "5";
    argv[2] = "4";
    argv[3] = "10";
    argv[4] = "5";
    argv[5] = "<";
    argv[6] = "f";
    argv[7] = "4";

    initialize_arg(argc, argv);

    pthread_create(&time_controller, NULL, (void *(*)(void *)) controller, (void *) max_time);
    pthreads_create(prod_id, p_num, producer);
    pthreads_create(cl_id, c_num, client);

    pthreads_wait(prod_id, p_num);
    pthreads_wait(cl_id, c_num);

    free_space();

    return 0;
}