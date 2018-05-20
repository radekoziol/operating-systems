//
// Created by radekkoziol on 16.05.18.
//
#include <stdio.h>
#include <zconf.h>
#include <memory.h>
#include <stdlib.h>
#include <math.h>
#include "library/utils.c"

void initialize_variables(char *pString[]) {
//
    th_num = 4;
    // c <= 3 <= 65
    c = 4;
    memset(thread_id, -1, sizeof(thread_id));

//    char in_img[MAX_PATH_LEN], in_filter_def[MAX_PATH_LEN], out_im[MAX_PATH_LEN];
    in_img = malloc(MAX_PATH_LEN);
    in_filter_def = malloc(MAX_PATH_LEN);
    out_img = malloc(MAX_PATH_LEN);

    in_img = "../ex_images/lena.ascii.pgm";
    in_filter_def = "../ex_filters/2.txt";
    out_img = "../ex_images/output.ascii.pgm";

    int ret;
    if ((ret = extract_description(&w, &h, &m)) < 0) {
        printf("Wrong file format! Error num: %d\n", ret);
        exit(EXIT_FAILURE);
    }

    printf("[Parent] weight = %d, height = %d, shades = %d\n", w, h, m);

    in_pix = (short **) malloc((w + 1) * sizeof(short *));
    for (int i = 0; i < w + 1; i++)
        in_pix[i] = (short *) malloc((h + 1) * sizeof(short));

    out_pix = (short **) malloc((w + 1) * sizeof(short *));
    for (int i = 0; i < w + 1; i++)
        out_pix[i] = (short *) malloc((h + 1) * sizeof(short));

    if ((ret = extract_image(ret)) < 0) {
        printf("Wrong file format! Error num: %d\n", ret);
        exit(EXIT_FAILURE);
    }

    printf("[Parent] Successfully processed image!\n");

    if ((ret = extract_filter()) < 0) {
        printf("Wrong file format! Error num: %d\n", ret);
        exit(EXIT_FAILURE);
    }
    // or this
    // Allocating
//    filter = (float **) malloc((c + 1) * sizeof(float *));
//    for (int i = 0; i < c + 1; i++)
//        filter[i] = (float *) malloc((c + 1) * sizeof(float));
//
//    get_random_filter_array();

//    for (int i = 0; i < c; i++) {
//        for (int j = 0; j < c; j++)
//            printf("%f ", filter[j][i]);
//        printf("\n");
//    }


    printf("[Parent] Successfully generated filter matrix!\n");


}

void write_to_output_file() {
    int ret;

    FILE *file = fopen(out_img, "w");
    if (file == NULL) {
        error_and_die("fopen");
    }

    // Adding header
    fwrite("P2\n", strlen("P2\n"), sizeof(char), file);
    fwrite("# filtered by RK\n", strlen("# filtered by RK\n"), sizeof(char), file);

    // Adding description
    char buf[128];
    memset(buf, '\0', 128);

    sprintf(buf, "%d %d\n%d\n", w, h, m);
    fwrite(buf, strlen(buf), sizeof(char), file);

    char pixel[8];
    // Adding pixels
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {

            memset(pixel, '\0', 8);
            sprintf(pixel, "%d ", out_pix[i][j]);

            fwrite(pixel, sizeof(char), strlen(pixel), file);
        }
        memset(pixel, '\0', 8);
        sprintf(pixel, "%d\n", out_pix[i][w-1]);
        fwrite(pixel, sizeof(char), strlen(pixel), file);
    }


    fclose(file);
}

int
main(int argc, char *argv[]) {


    printf("[Parent] Reading image..\n");

    initialize_variables(argv);

    print_pixels();

    pthreads_create(th_num, filter_image);

    pthreads_wait(th_num);
//
    print_pixels();
//
    write_to_output_file();
//
    printf("[Parent] Done!\n");

    free(filter);
    free(in_pix);
    free(out_pix);

    return 0;
}