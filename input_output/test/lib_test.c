//
// Created by radekkoziol on 15.03.18.
//
#include "../library/lib_io.c"


void sort_lib_test(char * path, char * path2, unsigned int record_num, unsigned int record_length){

    sort_lib(path, record_num, record_length);
}

void copy_lib_test(char * path1, char * path2, unsigned int record_num, unsigned int record_length){
    copy_lib(path1,path2,record_length*record_num);
}