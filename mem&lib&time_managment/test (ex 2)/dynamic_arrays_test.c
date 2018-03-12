//
// Created by radekkoziol on 11.03.18.
//
#include <time.h>
#include "../library (ex 1)/block_arrays_dynamically.c"
#include "../library (ex 1)/block_arrays_statically.h"
#include "random.c"
#include <string.h>


char * parse_to_string(struct timeval start, struct timeval end){

    __time_t sec_diff = end.tv_sec - start.tv_sec;
    __suseconds_t usec_diff = end.tv_usec - start.tv_usec ;

    static char array1[10];
    char array2[10];
    char dot [2] = ".";

    sprintf(array1, "%ld", sec_diff);
    sprintf(array2, "%ld", usec_diff);

    strcat(array1,dot);
    strcat(array1,array2);


    return array1;
}

void create_array_d_test(){

    struct DynamicBlock* blocks = create_array_d();

    free(blocks);

}


struct DynamicBlock* get_random_blocks_from_d(struct DynamicBlock *blocks, unsigned int size){

    for(int i = 0; i < size; i++){
        unsigned int n = rand() % (size * 2);
        add_block_d(&blocks,blocks[n]);
    }

    return blocks;

}

struct DynamicBlock* generate_blocks_array(unsigned int array_size, unsigned int block_size) {

    struct DynamicBlock* blocks;
    for(int i = 0; i < array_size; i++){
        struct DynamicBlock block;
        block.size = block_size;
        block.string = generate_random_string(block_size);
        add_block_d(&blocks,block);
    }

    return blocks;

}



void add_blocks_d_test() {

    struct DynamicBlock *blocks;

    struct DynamicBlock *add_blocks = generate_blocks_array(ARR_SIZE,BLOCK_SIZE);

    add_blocks_d(&blocks, add_blocks);

}


void delete_blocks_d_test(){

    struct DynamicBlock* blocks = generate_blocks_array(ARR_SIZE,BLOCK_SIZE);

    struct DynamicBlock *test_blocks = get_random_blocks_from_d(blocks,ARR_SIZE/2);

    delete_blocks_d(&blocks, test_blocks);

}

void closest_block_sum_to_d_test(){

    int x = 1233;

    struct DynamicBlock* blocks = generate_blocks_array(ARR_SIZE,BLOCK_SIZE);

    struct DynamicBlock block = closest_block_sum_to_d(x,blocks);

}

void re_adding_to_array_d_test(){

    struct DynamicBlock* blocks = generate_blocks_array(ARR_SIZE,BLOCK_SIZE);

    struct DynamicBlock *test_blocks = get_random_blocks_from_d(blocks,ARR_SIZE/2);

    delete_blocks_d(&blocks, test_blocks);

    add_blocks_d(&blocks, test_blocks);

}



