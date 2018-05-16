//
// Created by radekkoziol on 16.05.18.
//

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <memory.h>
#include "main.h"

void
error_and_die(char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

void pthreads_create(int num, void *fun) {
    for (int i = 0; i < num; i++) {
        if (pthread_create(&thread_id[i], NULL, fun, NULL) != 0)
            error_and_die("pthread_create");
    }
}

void pthreads_wait(int num) {
    // wait here for child
    for (int i = 0; i < num; i++)
        pthread_join(thread_id[i], NULL);

}


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

int read_next_pixel(const char *line, int *c_indic) {

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


    int ret;
    if ((ret = (int) strtol(pix, NULL, 10)) < 0) {
        printf("This pixel %s seems not to be number!\n", pix);
        exit(EXIT_FAILURE);
    }

    *c_indic = c;

    return ret;

}

/* start_line indicates line which real image starts */
int extract_image(int start_line) {

    int ret = 0;

    FILE *file = fopen(in_img, "r");
    if (file == NULL) {
        error_and_die("fopen");
    }


    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int l_num = 0;

    while ((read = getline(&line, &len, file)) != -1) {
        // Assuming no errors in input
        if (l_num > start_line) {

            c = 0;
            int pix_c = 0;
            while (line[c] != '\n') {
                pix[pix_c][start_line] =
                        (short) read_next_pixel(line, &c);
                pix_c++;
            }

            start_line++;

        } else if (l_num == start_line) {
            start_line = 0;
            // So as not to let this go to first if again
            l_num = h+1;
        } else {
            l_num++;
        }
    }

    fclose(file);

    if (line)
        free(line);


    return ret;

}
