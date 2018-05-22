//
// Created by radekkoziol on 16.05.18.
//
#include <stdio.h>
#include <memory.h>
#include <stdlib.h>
#include "../library/utils.c"
#include "../library/filter.c"


int
main(int argc, char *argv[]) {

    // Example input
//    argv[1] = "4";
//    argv[2] = "../ex_images/lena.ascii.pgm";
//    argv[3] = "../ex_filters/1.txt";
//    argv[4] = "../ex_images/output.ascii.pgm";
//    argv[4] = "test";
//    argc = 5;

    if (argc > 1 && (strcmp(argv[1], "test") == 0)) {

        argv[1] = "4";
        argv[2] = "../ex_images/lena.ascii.pgm";
        argv[3] = "../ex_images/output.ascii.pgm";

        initialize_variables(argv, argc);

        printf("[Parent] Performing tests!\n");
        // average of 5 runs for 1,2..,10 threads
        perform_test(5, 10);

    } else {
        if ((argc < 4) || argc > 6 || strcmp(argv[1], "-help") == 0) {
            printf("Arguments are: \n"
                   "   th_num in_img filter_path(opt) out_img"
                   "   test(opt) \n"
            );
            exit(0);
        }

        initialize_variables(argv, argc);

//    print_pixels(filter,c,c);

        pthreads_create(th_num, filter_image);

        pthreads_wait(th_num);

        write_to_output_file();
        free_ar();

        printf("[Parent] Done!\n");
    }


    return 0;
}