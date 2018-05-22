//
// Created by radekkoziol on 16.05.18.
//

#ifndef THREADS_MAIN_H
#define THREADS_MAIN_H

#include <zconf.h>

#define MAX_THREAD_NUM 128
#define MAX_PATH_LEN 128
#define MAX_BUF 65536

pthread_t thread_id[MAX_THREAD_NUM];
void *filter_image(int N);

// paths
char in_img[MAX_PATH_LEN], in_filter_def[MAX_PATH_LEN], out_img[MAX_PATH_LEN];
int w,h,m,c,th_num;
short **in_pix, **out_pix;
float **filter;


#endif //THREADS_MAIN_H
