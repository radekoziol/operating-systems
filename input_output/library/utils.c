//
// Created by radekkoziol on 13.03.18.
//


#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

char get_random_char(){
    return (char) ('A' + (random() % 26));
}


char ** generate_array(unsigned int record_num, unsigned int record_length ){

    char **records = calloc(record_num, sizeof(char*));
    if(!records) return NULL;

    for(int i = 0; i < record_num; i++) {
        records[i] = calloc(record_length, sizeof(char));
    }

    for(int i = 0; i < record_num; i++){
        for(int j = 0; j < record_length; j++){
            records[i][j] = get_random_char();
        }
    }

    return records;


}


bool sorted(unsigned int length, const char string1[length], const char string2[length]) {

    for (int i = 0; i < length; i++) {
        if (string1[i] < string2[i])
            return true;
        else if (string1[i] > string2[i])
            return false;
    }
    // Are equal
    return true;
}
