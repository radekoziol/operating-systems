//
// Created by radekkoziol on 16.05.18.
//
#include <stdio.h>
#include <zconf.h>
#include <memory.h>
#include <stdlib.h>
#include "../library/utils.c"
#include "../library/filter.c"


int
main(int argc, char *argv[]) {


    argv[1] = "4";
    argv[2] = "../ex_images/lena.ascii.pgm";
    argv[3] = "../ex_filters/2.txt";
    argv[4] = "../ex_images/output.ascii.pgm";

    initialize_variables(argv);

//    print_pixels();

    pthreads_create(th_num, filter_image);

    pthreads_wait(th_num);

//    print_pixels();

    write_to_output_file();


    printf("[Parent] Done!\n");


//    printf("[Parent] Performing tests!\n");
//
//    int i = 1;
//    while(i < 11) {
//        th_num = i;
//        printf("\n**** Thread number = %d\n", i);
//        perform_test(5);
//        i++;
//    }

    free(filter);
    free(in_pix);
    free(out_pix);

    return 0;
}