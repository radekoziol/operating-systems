//
// Created by radekkoziol on 10.03.18.
//

#ifndef MEM_LIB_TIME_MANAGMENT_BLOCK_H
#define MEM_LIB_TIME_MANAGMENT_BLOCK_H

#include <stdlib.h>

struct Block{

    // Actual string
    char *  string;

    // Length of string
    int size;

};

bool are_equal_blocks(struct Block block1, struct Block block2) {

    /*
        If blocks differ in size then false
        else we check each char
     */
    if(block1.size != block2.size)
        return false;
    else
        for(int i = 0; i < block1.size; i++) {
            if (block1.string[i] != block2.string[i])
                return false;
        }

    return true;
}


#endif //MEM_LIB_TIME_MANAGMENT_BLOCK_H
