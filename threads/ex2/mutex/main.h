//
// Created by radekkoziol on 27.05.18.
//


#include <stdio.h>
#include <zconf.h>
#include <stdlib.h>
#include <asm/errno.h>
#include <pthread.h>
#include <stdbool.h>


#ifndef EX2_MAIN_H
#define EX2_MAIN_H

#define MAX_BUF_SIZE 1024
#define MAX_PRODUCERS_NUM 128
#define MAX_CLIENTS_NUM 128


char *buffer[MAX_BUF_SIZE];

// Threads
pthread_t prod_id[MAX_PRODUCERS_NUM];
pthread_t cl_id[MAX_CLIENTS_NUM];
pthread_t time_controller;

// Input
unsigned int buf_size, c_num, p_num, fix_len,max_time;
char comp = '\0';
bool print_more_info = false;

// Counters
int cl_counter = 0;
int pr_counter = 0;

// Mutex, cond
pthread_mutex_t *mutex, cl_c, pr_c, line_mut;
pthread_cond_t **cond;

//
FILE *f;

#endif //EX2_MAIN_H
