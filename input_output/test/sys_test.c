//
// Created by radekkoziol on 15.03.18.
//
#include "../library/sys_io.c"

void sort_sys_test(char * path, char * path2, unsigned int record_num, unsigned int record_length){
    sort_sys(path, record_num, record_length);
}

void copy_sys_test(char * path1, char * path2, unsigned int record_num, unsigned int record_length){
    copy_sys(path1,path2,record_length*record_num);
}