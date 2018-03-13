//
// Created by radekkoziol on 11.03.18.
//
#include <time.h>
#include "../library (ex 1)/block_arrays_dynamically.c"
#include "../library (ex 1)/block_arrays_statically.h"
#include "random.c"
#include <string.h>
#define ARR_SIZE 1000
#define BLOCK_SIZE 10


void create_array_d_test(){

    struct DynamicBlock* blocks = create_array_d(ARR_SIZE);

    free(blocks);

}


struct DynamicBlock* get_random_blocks_from_d(struct DynamicBlock *blocks, unsigned int size){

    struct DynamicBlock* rand_blocks = create_array_d(size);

    for(int i = 0; i < size; i++){
        unsigned int n = rand() % (size * 2);
        add_block_d(&rand_blocks,blocks[n]);
    }

    return rand_blocks;

}

struct DynamicBlock* generate_blocks_array(unsigned int array_size, unsigned int block_size) {

    struct DynamicBlock* blocks = create_array_d(array_size);

    for(int i = 0; i < array_size; i++){
        struct DynamicBlock block;
        block.size = block_size;
        block.string = generate_random_string(block_size);
        add_block_d(&blocks,block);

    }

    return blocks;

}



void add_blocks_d_test() {

    struct DynamicBlock *blocks = create_array_d(ARR_SIZE);

    struct DynamicBlock *add_blocks = generate_blocks_array(ARR_SIZE,BLOCK_SIZE);

    add_blocks_d(&blocks, add_blocks);

    free(blocks);
    free(add_blocks);


}


void delete_blocks_d_test(){

    struct DynamicBlock* blocks = generate_blocks_array(ARR_SIZE,BLOCK_SIZE);

    struct DynamicBlock *test_blocks = get_random_blocks_from_d(blocks,ARR_SIZE/2);

    delete_blocks_d(&blocks, test_blocks);


}

void closest_block_sum_to_d_test(){

    int x = 798;

    struct DynamicBlock* blocks = generate_blocks_array(ARR_SIZE,BLOCK_SIZE);

    closest_block_sum_to_d(x,blocks);

    free(blocks);


}

void re_adding_to_array_d_test(){

    struct DynamicBlock* blocks = generate_blocks_array(ARR_SIZE,BLOCK_SIZE);

    struct DynamicBlock *test_blocks = get_random_blocks_from_d(blocks,ARR_SIZE/2);

    delete_blocks_d(&blocks, test_blocks);

    add_blocks_d(&blocks, test_blocks);


}



