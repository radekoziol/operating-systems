//
// Created by radekkoziol on 13.03.18.
//
#include <bits/types/FILE.h>
#include <zconf.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
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

void copy_sys(char *from, char *to, size_t file_size){


    int f1,f2;
    f1=open(from, O_RDONLY);
    f2=open(to,O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);

    struct stat st;

    stat("my_file.txt", &st);
    char copy[file_size];

    read(f1, copy , file_size);

    write(f2, copy , file_size);

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

    char path1[50] = "../file.txt";

    char path2[50] = "../file1.txt";



    generate_sys(path1, record_num, record_length);

    sort_sys(path1,record_num,record_length);

    copy_sys(path1,path2, record_length * record_num);
}