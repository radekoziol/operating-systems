//
// Created by radekkoziol on 13.03.18.
//


#include <stdlib.h>

char get_random_char(){
    return (char) ('A' + (random() % 26));
}

void generate_array(unsigned int record_num, unsigned int record_length ,char records [record_num][record_length] ){

    for(int i = 0; i < record_num; i++){
        for(int j = 0; j < record_length; j++){
            records[i][j] = get_random_char();
        }
    }

}