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

    int time_l = 100;
    int mem_l = 20;
    mem_l = 1048576*mem_l;

    char* path= "../file.txt";

    execute_file(path,time_l,mem_l);

//    if ((argc == 1) || strcmp(argv[1], "-help") == 0) {
//        printf("Arguments are: \n"
//                       "   path condition date (how)\n");
//        printf("Description: \n");
//        printf(" Possible conditions: \n"
//                       "  '>' modified later than <date> \n"
//                       "  '=' modified at the same <date> \n"
//                       "  '<' modified earlier than <date> \n");
//        printf(" Path must be in format day mm//dd/yy hh:mm:ss AM/PM "
//                       "f.e 'Tue 10/30/2001 10:59:10 AM'\n");
//        printf(" <how = 'sys'> (default) uses methods like opendir, ..\n"
//                       " <how = 'nftw' uses method nftw\n");
//        exit(0);
//    }
//    if (argc < 3) {
//        printf("You did not input enough arguments!\nFor more information write -help\n");
//        exit(0);
//    }
//
//    time_t input_date = parse_date(argv[3]);
//
//    char condition = argv[2][0];
//
//    switch (condition) {
//        case '>':
//            list_files
//                    (argv[1], is_later, input_date);
//        case '<':
//            list_files
//                    (argv[1], is_earlier, input_date);
//        case '=':
//            list_files
//                    (argv[1], is_equal, input_date);
//
//        default:
//            break;
//    }


    return 0;
}
