//
// Created by radekkoziol on 11.03.18.
//

#include "../library (ex 1)/block_arrays_dynamically.h"
#include "random.c"

struct DynamicBlock *get_random_blocks_from_d(struct DynamicBlock *blocks, unsigned int size){

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


void create_array_d_test(){

    struct DynamicBlock* blocks = create_array_d();

}
//
void add_blocks_d_test(struct DynamicBlock *blocks) {

    struct DynamicBlock *test_blocks;

    add_blocks_d(&test_blocks, blocks);

}


void delete_blocks_d_test(struct DynamicBlock *blocks, struct DynamicBlock *test_blocks ){

    delete_blocks_d(&blocks, test_blocks);

}


struct DynamicBlock closest_block_sum_to_d_test( struct DynamicBlock *blocks ,unsigned int x){

    struct DynamicBlock block = closest_block_sum_to_d(x,blocks);

}

void re_adding_to_array_d_test(struct DynamicBlock *test_blocks ,struct DynamicBlock *blocks){

    delete_blocks_d(&blocks, test_blocks);

    add_blocks_d(&blocks, test_blocks);

}


