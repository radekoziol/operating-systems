//
// Created by radekkoziol on 11.03.18.
//


#include <stdlib.h>

char get_random_char(){
    return (char) ('A' + (random() % 26));
}

char * generate_random_string(unsigned int size){

    char* string = (char *)calloc((size_t) size, sizeof(char *));

    for(int i = 0; i < size; i++){
        string[i] = get_random_char();
    }

    return string;
}
