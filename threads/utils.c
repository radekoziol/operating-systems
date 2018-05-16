//
// Created by radekkoziol on 16.05.18.
//

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <memory.h>
#include "main.h"

void
error_and_die(char *msg){
    perror(msg);
    exit(EXIT_FAILURE);
}

void pthreads_create(int num, void * fun) {
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

    int error = 0;

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
    int l_n = 0;
    while ((read = getline(&line, &len, file)) != -1) {

        if (line[0] != '#' && read > 1) {
            if (l_n == 0) {
                if (line[0] != 'P' || line[1] != '2') {
                    error = -1;
                    break;
                }
            } else if (l_n == 1) {
                int c1 = 0;
                while (line[c1] != ' ' && c1 < read) {
                    wgth[c1] = line[c1];
                    c1++;
                }

                c1++;
                int c2 = 0;
                while (line[c1] != '\n' && c1 < read) {
                    hgth[c2] = line[c1];
                    c1++; c2++;
                }

            } else if (l_n == 2) {
                int c1 = 0;
                while (line[c1] != '\n' && c1 < read) {
                    shds[c1] = line[c1];
                    c1++;
                }
            }

            l_n++;
        }

        if (l_n == 3)
            break;
    }

    fclose(file);

    if (line)
        free(line);

    if ((*w = (int) strtol(wgth, NULL, 10)) == 0)
        error = -2;
    else if ((*h = (int) strtol(hgth, NULL, 10)) == 0)
        error = -3;
    else if ((*m = (int) strtol(shds, NULL, 10)) == 0)
        error = -4;

    return error;
}