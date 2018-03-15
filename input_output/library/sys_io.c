//
// Created by radekkoziol on 13.03.18.
//
#include <bits/types/FILE.h>
#include <zconf.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include "utils.h"


void generate_sys(char *path, unsigned int record_num, unsigned int record_length){

    char ** records;

    records = generate_array(record_num, record_length);

    int fd = open(path, O_WRONLY);

    if(fd < 0){
        printf("Error opening file!\n");
        exit(-1);
    }

    for(int i = 0; i < record_num; i++) {
        write(fd, records[i] ,sizeof(char)*record_length);
        write(fd, "\n" ,sizeof(char)*1);
    }

}

void sort_sys(char *path, unsigned int record_num, unsigned int record_length) {

    int fd = open(path, O_RDWR);

    if(fd < 0){
        printf("Error opening file!\n");
        exit(-1);
    }

    unsigned int string_l = (record_length + 1);
    // Only 2 strings will be stored
    char blocks[2][record_length];


    for (int i = 0; i < record_num; i++) {

        // Iterating over each string
        lseek(fd, i*string_l, SEEK_SET);

        //Reading
        read(fd, blocks[0] ,sizeof(char)*string_l);

        // Setting to beginning of file for next loop
        lseek(fd, 0, SEEK_SET);

        // Creating sorted file
        for (int j = 0; j < i; j++) {

            read(fd, blocks[1] , sizeof(char)*string_l);

            // If not sorted swap them
            if (!sorted(record_length, blocks[1], blocks[0])) {

                // Note that compared do lib, offset cannot be negative!
                lseek(fd, j*string_l , SEEK_SET);
                write(fd, blocks[0] , sizeof(char) * record_length);

                lseek(fd, i*string_l, SEEK_SET);
                write(fd, blocks[1] , sizeof(char) * record_length);


                // We need to need to check again for swapped string
                i--;
                break;
            }
        }


    }

}

void hello1(){

    unsigned int record_length = 10;
    unsigned int record_num = 100;

    char pathname[100] = "../file.txt";


    generate_sys(pathname, record_num, record_length);

    sort_sys(pathname,record_num,record_length);
}