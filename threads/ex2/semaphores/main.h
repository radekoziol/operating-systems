//
// Created by radekkoziol on 27.05.18.
//


#include <stdio.h>
#include <zconf.h>
#include <stdlib.h>
#include <asm/errno.h>
#include <pthread.h>


#ifndef EX2_MAIN_H
#define EX2_MAIN_H

#define MAX_BUF_SIZE 1024
#define MAX_PRODUCERS_NUM 128
#define MAX_CLIENTS_NUM 128


char *buffer[MAX_BUF_SIZE];

pthread_t prod_id[MAX_PRODUCERS_NUM];
pthread_t cl_id[MAX_CLIENTS_NUM];

volatile int cl_counter = 0;
volatile int pr_counter = 0;
sem_t **sem;
sem_t cl_c, pr_c;




int x;


#endif //EX2_MAIN_H
