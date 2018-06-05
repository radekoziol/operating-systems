

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <signal.h>
#include "main.h"
#include "library/utils.c"

int main(int argc, char *argv[]) {

    // Example input
    //    "<p_num> <c_num>
    // <buf_size> <fix_len> <comparator> <print> <max_time>");
//    argc = 7;
//    argv[1] = "4";
//    argv[2] = "5";
//    argv[3] = "10";
//    argv[4] = "5";
//    argv[5] = "<";
//    argv[6] = "true";
//    argv[7] = "5";

    initialize_arg(argc, argv);

    pthread_create(&end_pr, NULL, (void *(*)(void *)) controller, (void *) (intptr_t) max_time);
    pthreads_create(prod_id, p_num, producer);
    pthreads_create(cl_id, c_num, client);

    pthreads_wait(cl_id, c_num);
    pthreads_wait(prod_id, p_num);

    return 0;
}