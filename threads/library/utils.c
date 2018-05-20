//
// Created by radekkoziol on 16.05.18.
//

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <memory.h>
#include "../main.h"

void error_and_die(char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void pthreads_create(int num, void *fun) {
    for (int i = 0; i < num; i++) {
        if (pthread_create(&thread_id[i], NULL, fun, (void *) i) != 0)
            error_and_die("pthread_create");
    }
}

void pthreads_wait(int num) {
    // wait here for child
    for (int i = 0; i < num; i++)
        pthread_join(thread_id[i], NULL);

}

/* On success returns number of lines read */
int extract_description(int *w, int *h, int *m) {

    int ret;

    FILE *file = fopen(in_img, "r");
    if (file == NULL) {
        error_and_die("fopen");
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


    if(pix[0] == '\0')
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


    if(pix[0] == '\0')
        return 0;

    char *end_ptr;
    int ret = (int) strtol(pix, &end_ptr,10);
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
        perror("Error while opening file");
        exit(EXIT_FAILURE);
    }

    char *line = NULL;
    size_t len = 0;
    while(start_line != 1){
        if( getline(&line, &len, file) == -1){
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
        error_and_die("fopen");
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

void print_pixels() {
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++)
            printf("%d ", in_pix[j][i]);
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

    int prec = 1000;
    srand((unsigned int) time(NULL));

    for (int i = 0; i < c; i++)
        for (int j = 0; j < c; j++)
            filter[i][j] = (float) rand() / (float) (RAND_MAX);


    float f_sum = sum(filter);
    while (!(f_sum > 0.99 && f_sum < 1.11)) {
        int i = rand() % c;
        int j = rand() % c;

//        printf("i= %d j= %d\n", i, j);

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
//                    filter[i][j] += 0.007;
//                    counter--;
//                    if (counter == 0)
//                        break;
//                }


    }

}
