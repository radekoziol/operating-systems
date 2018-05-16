//
// Created by radekkoziol on 16.05.18.
//

#ifndef THREADS_MAIN_H
#define THREADS_MAIN_H

#define MAX_THREAD_NUM 128
#define MAX_PATH_LEN 128
#define MAX_BUF 65536

pthread_t thread_id[MAX_THREAD_NUM];

// paths
char * in_img, *in_filter_def, *out_img;
int w,h,m,c,th_num;
short **pix;
float **filter;


#endif //THREADS_MAIN_H
