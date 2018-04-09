//
// Created by radekkoziol on 09.04.18.
//

#include <zconf.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int get_random_signal() {
    return 0;
}

// Sets global arrays to default
void set_arr(int size, int child_pid[], int child_status[], int child_work[]) {
    for (int j = 0; j < size; j++) {
        child_status[j] = 0;
        child_pid[j] = -10;
        child_work[j] = 0;
    }
}

void print_info(int size, int child_pid[], int child_status[],int child_work[]) {

    printf("\n**********************************\n");

    for (int j = 0; j < size; j++){
        printf("Process %d:\n"
                       " - executed with status %d\n"
                       " - worked for %d sec\n",
               child_pid[j], child_status[j],child_work[j]);
    }


    printf("\n**********************************\n");

}
