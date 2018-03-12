//
// Created by radekkoziol on 11.03.18.
//


#include <time.h>
#include <stdio.h>
#include "../library (ex 1)/block_arrays_statically.c"
#include "random.h"



struct StaticBlock blocks[ARR_SIZE];

void generate_blocks_array_s() {

    for(int i = 0; i < ARR_SIZE; i++){
        struct StaticBlock block;
        for(int j = 0; j < BLOCK_SIZE; j++)
            block.string[j] = get_random_char();

        add_block_s(blocks,block);
    }

}


struct StaticBlock *get_random_blocks_from_s(const int size){

    struct StaticBlock* block = (struct StaticBlock*) calloc(size, sizeof(struct StaticBlock));

    for(int i = 0; i < size; i++){
        unsigned int n = (unsigned int) (rand() % (size * 2));
        add_block_s(block,blocks[n]);
    }

    return block;
}

void add_blocks_s_test() {

    struct StaticBlock test_blocks [ARR_SIZE];

    add_blocks_s(test_blocks, blocks);

}

void delete_blocks_s_test(){

    struct StaticBlock *test_blocks= get_random_blocks_from_s(ARR_SIZE/2);
    test_blocks->size = ARR_SIZE/2;

    delete_blocks_s(blocks, test_blocks);

}


void closest_block_sum_to_s_test(){

    int x = 1234;

    struct StaticBlock block = closest_block_sum_to_s(x,blocks);

}

void re_adding_to_array_s_test(){

    struct StaticBlock *test_blocks = get_random_blocks_from_s(ARR_SIZE/2);

    delete_blocks_s(blocks, test_blocks);

    add_blocks_s(blocks, test_blocks);

}





