//
// Created by radekkoziol on 11.03.18.
//

#ifndef MEM_LIB_TIME_MANAGMENT_BLOCK_ARRAYS_DYNAMICALLY_H
#define MEM_LIB_TIME_MANAGMENT_BLOCK_ARRAYS_DYNAMICALLY_H

//
// Created by radekkoziol on 28.02.18.
//
#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>

struct DynamicBlock{

    // Actual string
    char *  string;

    // Length of string
    int size;

};

bool are_equal_blocks_d(struct DynamicBlock block1, struct DynamicBlock block2);

struct DynamicBlock * create_array_d();

void delete_array_d(struct DynamicBlock * array);

void add_blocks_d(struct DynamicBlock ** array, struct DynamicBlock* blocks);

void add_block_d(struct DynamicBlock ** array, struct DynamicBlock block);

void delete_blocks_d(struct DynamicBlock ** array, struct DynamicBlock * blocks);

struct DynamicBlock closest_block_sum_to_d(int x, struct DynamicBlock * array);



#endif //MEM_LIB_TIME_MANAGMENT_BLOCK_ARRAYS_DYNAMICALLY_H
