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
// Main buffer
char *buffer[MAX_BUF_SIZE];

// Threads
pthread_t prod_id[MAX_PRODUCERS_NUM];
pthread_t cl_id[MAX_CLIENTS_NUM];
pthread_t end_pr;

// Input
unsigned int buf_size, c_num, p_num, fix_len,max_time;
char comp = '\0';
bool print_more_info = false;

// Read line counters
int cl_counter = 0;
int pr_counter = 0;

// Semaphores
sem_t **sem, cl_c, pr_c, line_sem;

FILE* file;


#endif //EX2_MAIN_H
