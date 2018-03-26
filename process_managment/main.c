//
// Created by radekkoziol on 18.03.18.
//

#if defined(__linux__) || defined(__MINT__)
# define _GNU_SOURCE /* strptime(), getsubopt() */

#endif

#include <wait.h>
#include <bits/types/FILE.h>
#include <zconf.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "library/utils.c"

int
main(int argc, char **argv) {


    if ((argc == 1) || strcmp(argv[1], "-help") == 0) {
        printf("Arguments are: \n"
                       "   path time_limit memory_limit \n");

    }

//    Example input
    argv[0] = "../file.txt";
    argv[1] = "10";
    argv[2] = "100";


    int time_l = (int) strtol(argv[1], NULL, 10);
    int mem_l = (int) strtol(argv[2], NULL, 10);
    mem_l = 1048576*mem_l;

    char* path= argv[0];

    execute_file(path,time_l,mem_l);


    return 0;
}
