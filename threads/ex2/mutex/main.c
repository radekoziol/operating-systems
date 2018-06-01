

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#include "main.h"
#include "library/utils.c"


int main(int argc, char *argv[]) {

    // Example input
//    argc = 7;
//    argv[1] = "5";
//    argv[2] = "4";
//    argv[3] = "10";
//    argv[4] = "5";
//    argv[5] = "<";
//    argv[6] = "f";
//    argv[7] = "0";

    initialize_arg(argc, argv);

    pthread_create(&time_controller, NULL, (void *(*)(void *)) controller, (void *) (intptr_t)max_time);
    pthreads_create(prod_id, p_num, producer);
    pthreads_create(cl_id, c_num, client);

    pthreads_wait(prod_id, p_num);
    pthreads_wait(cl_id, c_num);


    return 0;
}