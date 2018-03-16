//
// Created by radekkoziol on 16.03.18.
//
#include <glob.h>
#include "../test/utils.h"

#ifndef INPUT_OUTPUT_LIB_IO_H
#define INPUT_OUTPUT_LIB_IO_H

void sort_lib(char *path, unsigned int record_num, unsigned int record_length) ;
void copy_lib(char *from, char *to, size_t file_size);
bool sorted_lib(unsigned int length, const char string1[length], const char string2[length]);


#endif //INPUT_OUTPUT_LIB_IO_H
