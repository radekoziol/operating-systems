//
// Created by radekkoziol on 11.03.18.
//

#define ARR_SIZE 1000


#include "../library (ex 1)/block_arrays_statically.h"
#include "random.c"
#include "../library (ex 1)/block_arrays_dynamically.h"

struct StaticBlock blocks[ARR_SIZE];

void generate_blocks_array_s() {

    for(int i = 0; i < ARR_SIZE; i++){
        struct StaticBlock block;
        for(int j = 0; j < BLOCK_SIZE; j++)
            block.string[j] = get_random_char();

        add_block_s(blocks,block);
    }

}


struct StaticBlock *get_random_blocks_from_s(struct StaticBlock blocks[ARR_SIZE], unsigned int size){

    for(int i = 0; i < size; i++){
        unsigned int n = rand() % (size * 2);
        add_block_s(blocks,blocks[n]);
    }

    return blocks;
}

void add_blocks_s_test(struct StaticBlock *test_blocks) {

    add_blocks_s(blocks, test_blocks);

}

void delete_blocks_d_test(struct StaticBlock *test_blocks ){


}


struct StaticBlock closest_block_sum_to_d_test(unsigned int x){

    struct StaticBlock block = closest_block_sum_to_s(x,blocks);

}

void re_adding_to_array_s_test(struct StaticBlock *test_blocks){

    delete_blocks_s(blocks,test_blocks);

    add_blocks_s(blocks, test_blocks);

}


