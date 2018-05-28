

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#include "main.h"
#include "utils.c"


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

    sem = (sem_t **) malloc((size_t) max(c_num, p_num) * sizeof(sem_t *));
    for (int i = 0; i < max(c_num, p_num); i++) {
        for (int j = 0; j < 2; j++) {
            sem[i] = (sem_t *) malloc(2 * sizeof(sem_t *));
        }
    }
    for (int i = 0; i < max(c_num, p_num); i++) {
        for (int j = 0; j < 2; j++) {
            sem_init(&sem[i][j], 0, 1);
        }
    }

    memset(is_cl_alive, true, (size_t) max(c_num, p_num));
    memset(is_prod_alive, true, (size_t) max(c_num, p_num));
}

void free_space() {
    for (int i = 0; i < max(c_num, p_num); i++) {
        for (int j = 0; j < 2; j++)
            sem_destroy(&sem[i][j]);
    }
    sem_destroy(&cl_c);
    sem_destroy(&pr_c);
    sem_destroy(&line_sem);

    free(sem);
}


void controller(int t) {

    sleep((unsigned int) t);

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

int main(int argc, char *argv[]) {

    // Example input
    argc = 7;
    argv[1] = "5";
    argv[2] = "6";
    argv[3] = "10";
    argv[4] = "5";
    argv[5] = "<";
    argv[6] = "t";
    argv[7] = "4";

    initialize_arg(argc, argv);

    pthread_create(&time_controller, NULL, (void *(*)(void *)) controller, (void *) max_time);
    pthreads_create(cl_id, c_num, client);
    pthreads_create(prod_id, p_num, producer);

    pthreads_wait(prod_id, p_num);
    pthreads_wait(cl_id, c_num);

    free_space();

    return 0;
}