//
// Created by radekkoziol on 16.05.18.
//

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <memory.h>
#include <sys/time.h>
#include "../main/main.h"


void error_and_die(char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void pthreads_create(int num, void *fun) {
    for (int i = 0; i < num; i++) {
        if (pthread_create(&thread_id[i], NULL, fun, (void *) (intptr_t) i) != 0)
            error_and_die("pthread_create");
    }
}

void pthreads_wait(int num) {
    // wait
    for (int i = 0; i < num; i++)
        pthread_join(thread_id[i], NULL);

}

/* On success returns number of lines read */
int extract_description(int *w, int *h, int *m) {

    int ret;

    FILE *file = fopen(in_img, "r");
    if (file == NULL) {
        error_and_die(in_img);
    }

    char wgth[8];
    char hgth[8];
    char shds[8];
    memset(wgth, '\0', 8);
    memset(hgth, '\0', 8);
    memset(shds, '\0', 8);

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int l_num = 0;
    while ((read = getline(&line, &len, file)) != -1) {

        if (line[0] != '#' && read > 1) {
            if (l_num == 0) {
                if (line[0] != 'P' || line[1] != '2') {
                    ret = -1;
                    break;
                }
            } else if (l_num == 1) {
                int c1 = 0;
                while (line[c1] != ' ' && c1 < read) {
                    wgth[c1] = line[c1];
                    c1++;
                }

                c1++;
                int c2 = 0;
                while (line[c1] != '\n' && c1 < read) {
                    hgth[c2] = line[c1];
                    c1++;
                    c2++;
                }

            } else if (l_num == 2) {
                int c1 = 0;
                while (line[c1] != '\n' && c1 < read) {
                    shds[c1] = line[c1];
                    c1++;
                }
            }

            l_num++;
        }

        if (l_num == 3)
            break;
    }

    fclose(file);

    if (line)
        free(line);

    ret = l_num;
    if ((*w = (int) strtol(wgth, NULL, 10)) == 0)
        ret = -2;
    else if ((*h = (int) strtol(hgth, NULL, 10)) == 0)
        ret = -3;
    else if ((*m = (int) strtol(shds, NULL, 10)) == 0)
        ret = -4;

    return ret;
}

float read_next_float(const char *line, int *c_indic) {

//    printf("%s\n", line);
    char pix[8];
    memset(pix, '\0', 8);

    int c = *c_indic;

    int pix_c = 0;
    while (line[c] == ' ')
        c++;

    while (line[c] != ' ' && line[c] != '\n') {
        pix[pix_c] = line[c];
        c++;
        pix_c++;
    }
    if (line[c] != '\n') c++;


    if (pix[0] == '\0')
        return 0;

    char *end_ptr;
    int ret = (int) strtof(pix, &end_ptr);
    if (pix == end_ptr) {
        printf("Unable to convert '%s'\n", pix);
        exit(EXIT_FAILURE);
    }

    *c_indic = c;

    return ret;

}

int read_next_pixel(const char *line, int *c_indic) {

//    printf("%s\n", line);
    char pix[8];
    memset(pix, '\0', 8);

    int c = *c_indic;

    int pix_c = 0;
    while (line[c] == ' ')
        c++;

    while (line[c] != ' ' && line[c] != '\n') {
        pix[pix_c] = line[c];
        c++;
        pix_c++;
    }
    if (line[c] != '\n') c++;


    if (pix[0] == '\0')
        return 0;

    char *end_ptr;
    int ret = (int) strtol(pix, &end_ptr, 10);
    if (pix == end_ptr) {
        printf("Unable to convert '%s'\n", pix);
        exit(EXIT_FAILURE);
    }

    *c_indic = c;

    return ret;

}

/* start_line indicates line number which real image starts */
int extract_image(int start_line) {

    FILE *file = fopen(in_img, "r");
    if (file == NULL) {
        error_and_die(in_img);
    }

    char *line = NULL;
    size_t len = 0;
    while (start_line != 1) {
        if (getline(&line, &len, file) == -1) {
            fclose(file);
            return -1;
        }
        start_line--;
    }

    short num;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            fscanf(file, "%hi%*[ \n]", &num);
            in_pix[i][j] = num;
        }
    }

    fclose(file);


    if (line)
        free(line);

    return 0;
}

int extract_filter() {

    int ret = 0;

    FILE *file = fopen(in_filter_def, "r");
    if (file == NULL) {
        error_and_die(in_img);
    }


    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    // Assuming though no errors in input like comment
    read = getline(&line, &len, file);
    if ((c = (int) strtol(line, NULL, 10)) < 0) {
        error_and_die("strtol: unable to read size!\n ");
    }

    // Allocating
    filter = (float **) malloc((c + 1) * sizeof(float *));
    for (int i = 0; i < c + 1; i++)
        filter[i] = (float *) malloc((c + 1) * sizeof(float));

    int line_n = 0;
    while ((read = getline(&line, &len, file)) != -1) {

        int c1 = 0;
        int pix_c = 0;
        while (line[c1] != '\n') {
            filter[pix_c]
            [line_n] =
                    read_next_float(line, &c1);
            pix_c++;
        }

        line_n++;
        line_n++;

    }

    fclose(file);

    if (line)
        free(line);


    return ret;

}

void print_pixels(float **ar, int x, int y) {
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++)
            printf("%f ", ar[j][i]);
        printf("\n");
    }
}

float sum(float **pDouble) {

    float sum = 0.0;
    for (int i = 0; i < c; i++)
        for (int j = 0; j < c; j++)
            sum += filter[i][j];

    return sum;
}

/* Assuming sum of filter array elements is 1*/
void get_random_filter_array() {

    srand((unsigned int) time(NULL));

    for (int i = 0; i < c; i++)
        for (int j = 0; j < c; j++)
            filter[i][j] = (float) rand() / (float) (RAND_MAX);


    float f_sum = sum(filter);
    while (!(f_sum > 0.999 && f_sum < 1.001)) {
        int i = rand() % c;
        int j = rand() % c;

        if (f_sum > 1)
            filter[i][j] /= rand() % c + 1;
        else
            filter[i][j] *= rand() % c + 1;
        f_sum = sum(filter);

        // dilution
//        int counter = 1;
//        for (int i = 0; i < c; i++)
//            for (int j = 0; j < c; j++)
//                if (filter[i][j] < 0.001) {
//                    filter[i][j] += 0.0005;
//                    counter--;
//                    if (counter == 0)
//                        break;
//                }

    }

}

void free_ar() {

    free(filter);
//    free(in_pix);
    free(out_pix);
}

void allocate_ar() {

    printf("[Parent] Allocating memory for img :weight = %d, height = %d, shades = %d\n", w, h, m);

    in_pix = (short **) malloc((w) * sizeof(short *));
    for (int i = 0; i < w + 1; i++)
        in_pix[i] = (short *) malloc((h) * sizeof(short));

    out_pix = (short **) malloc((w) * sizeof(short *));
    for (int i = 0; i < w + 1; i++)
        out_pix[i] = (short *) malloc((h) * sizeof(short));
}

void initialize_variables(char *argv[], int argc) {

    if ((th_num = (int) strtol(argv[1], NULL, 10)) == 0)
        error_and_die("strtol: can not parse thread number!\n");


    memset(in_img, '\0', MAX_PATH_LEN);
    strcpy(in_img, argv[2]);

    printf("[Parent] Reading image..\n");

    int ret;
    if ((ret = extract_description(&w, &h, &m)) < 0) {
        printf("Wrong file format! Error num: %d\n", ret);
        exit(EXIT_FAILURE);
    }

    allocate_ar();

    if ((ret = extract_image(ret)) < 0) {
        printf("Wrong file format! Error num: %d\n", ret);
        exit(EXIT_FAILURE);
    }

    printf("[Parent] Successfully processed image!\n");

    memset(out_img, '\0', MAX_PATH_LEN);
    memset(in_filter_def, '\0', MAX_PATH_LEN);

    if (argc > 4) {

        strcpy(in_filter_def, argv[3]);
        strcpy(out_img, argv[4]);

        if ((ret = extract_filter()) < 0) {
            printf("Wrong file format! Error num: %d\n", ret);
            exit(EXIT_FAILURE);
        }
        printf("[Parent] Successfully read filter matrix!\n");
    } else {

        strcpy(out_img, argv[3]);

        srand((unsigned int) time(NULL));

        // size [3,65]
        c = rand() % 63 + 3;

        filter = (float **) malloc((c + 1) * sizeof(float *));
        for (int i = 0; i < c + 1; i++)
            filter[i] = (float *) malloc((c + 1) * sizeof(float));

        get_random_filter_array();
        printf("[Parent] Successfully generated matrix!\n");
    }

}

void write_to_output_file() {

    FILE *file = fopen(out_img, "w");
    if (file == NULL) {
        error_and_die(out_img);
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
        sprintf(pixel, "%d\n", out_pix[i][w - 1]);
        fwrite(pixel, sizeof(char), strlen(pixel), file);
    }


    fclose(file);
}

void perform_test(int test_number, int max_th_num) {

    int i = 1;
    while (i < max_th_num) {

        th_num = i;
        printf("\n**** Thread number = %d\n", i);


        struct timeval dt;

        c = 3;
        while (c < 65) {

            filter = (float **) malloc((c + 1) * sizeof(float *));
            for (int j = 0; j < c + 1; j++)
                filter[j] = (float *) malloc((c + 1) * sizeof(float));

            get_random_filter_array();

            struct timeval t0, t1;
            gettimeofday(&t0, NULL);

            for (int j = 0; j < test_number; j++) {
                pthreads_create(th_num, filter_image);

                pthreads_wait(th_num);
            }

            gettimeofday(&t1, NULL);
            timersub(&t1, &t0, &dt);

            fprintf(stdout, "[Parent] Average of %d tests where c = %d, filtering took %d.%06d sec\n",
                    test_number, c, (int) dt.tv_sec / test_number, (int) dt.tv_usec / test_number);


            write_to_output_file();

            free(filter);

            c *= 2;
        }

        i++;
    }


    free_ar();
}

