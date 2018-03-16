//
// Created by radekkoziol on 13.03.18.
//

#include <stdio.h>
#include <stdlib.h>
#include "test/test.c"

unsigned int get_record_length(){
    return 10;
}

unsigned int get_record_num(){
    return 100;
}

char * get_first_file_path(){
    return "../file.txt";
};

char * get_second_file_path(){
    return "../file1.txt";
}

int main(int arc, char **argv){

//    hello();


    unsigned int record_length = get_record_length();
    unsigned int record_num = get_record_num();


    char * path1 = get_first_file_path();

    char * path2 = get_second_file_path();



    if (freopen("../report.txt", "w", stdout) == NULL)
    {
        perror("freopen() failed");
        return EXIT_FAILURE;
    }

    test(path1,path2,record_num,record_length);


    fclose(stdout);




//
//    unsigned int record_length = get_record_length();
//    unsigned int record_num = get_record_num();
//
//    char * path1 = calloc(50, sizeof(char));
//    path1 = get_first_file_path();
//
//    char * path2 = calloc(50, sizeof(char));
//    path2 = get_second_file_path();



}