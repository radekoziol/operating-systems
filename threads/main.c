//
// Created by radekkoziol on 16.05.18.
//
#include <stdio.h>
#include <zconf.h>
#include <memory.h>
#include <stdlib.h>
#include "utils.c"

void *
ex(void *arg) {
    printf("[Thread] Filtering my part!\n");
    // signal here: child is done
    return NULL;
}


void initialize_variables(char *pString[]) {
//
    th_num = 4;
    // c <= 3 <= 65
    c = 12;
    memset(thread_id, -1, sizeof(thread_id));

//    char in_img[MAX_PATH_LEN], in_filter_def[MAX_PATH_LEN], out_im[MAX_PATH_LEN];
    in_img = malloc(MAX_PATH_LEN);
    in_filter_def = malloc(MAX_PATH_LEN);
    out_img = malloc(MAX_PATH_LEN);

    in_img = "../ex_images/feep.ascii.pgm";
    in_filter_def = "";
    out_img = "../ex_images/output.ascii.pgm";

    int ret;
    if ((ret = extract_description(&w, &h, &m)) < 0) {
        printf("Wrong file format! Error num: %d\n", ret);
        exit(EXIT_FAILURE);
    }

    printf("[Parent] weight = %d, height = %d, shades = %d\n", w, h, m);

    pix = (short **) malloc((w + 1) * sizeof(short *));
    for (int i = 0; i < w + 1; i++)
        pix[i] = (short *) malloc((h + 1) * sizeof(short));

    // ??
    filter = (float **) malloc((c + 1) * sizeof(float *));
    for (int i = 0; i < c + 1; i++)
        filter[i] = (float *) malloc((c + 1) * sizeof(float));

    if ((ret = extract_image(ret)) < 0) {
        printf("Wrong file format! Error num: %d\n", ret);
        exit(EXIT_FAILURE);
    }

}


int
main(int argc, char *argv[]) {


    printf("[Parent]: Reading image..\n");

    initialize_variables(argv);

    printf("[Parent] Successfully processed image!\n");

    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++)
            printf("%d ", pix[j][i]);
        printf("\n");
    }



//    pthreads_create(th_num, ex);
//
//    pthreads_wait(th_num);
//
//    printf("parent: end\n");

    return 0;
}