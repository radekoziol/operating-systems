//
// Created by radekkoziol on 11.03.18.
//

#ifndef MEM_LIB_TIME_MANAGMENT_BLOCK_ARRAYS_STATICALLY_H
#define MEM_LIB_TIME_MANAGMENT_BLOCK_ARRAYS_STATICALLY_H
#define ARR_SIZE 1000
#define BLOCK_SIZE 10


struct StaticBlock{

    // Actual string
    char string [BLOCK_SIZE];

    // Length of string
    int size;

};

void add_blocks_s(struct StaticBlock array [], struct StaticBlock* blocks);

void add_block_s(struct StaticBlock array [], struct StaticBlock block);

void delete_blocks_s(struct StaticBlock array [], struct StaticBlock * blocks);

struct StaticBlock closest_block_sum_to_s(int x, struct StaticBlock blocks []);



#endif //MEM_LIB_TIME_MANAGMENT_BLOCK_ARRAYS_STATICALLY_H
