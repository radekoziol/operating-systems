//
// Created by radekkoziol on 28.02.18.
//
#include <stdio.h>


#include "block_arrays_statically.h"
#include <stdlib.h>
#include <stdbool.h>




struct StaticBlock blocks[ARR_SIZE];

void add_blocks_s(struct StaticBlock array [], struct StaticBlock* blocks){

    for(int i = 0; i < blocks->size; i++)
        add_block_s(array,blocks[i]);
}


void add_block_s(struct StaticBlock array [], struct StaticBlock block){

    for(int i = 0; i < ARR_SIZE; i++) {
        if (array[i].size == 0){
            array[i] = block;
            return;
        }
    }


    printf("Block array is full!");

}

bool are_equal_blocks_s(struct StaticBlock block1, struct StaticBlock block2) {

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

void delete_blocks_s(struct StaticBlock array [], struct StaticBlock * blocks){

    int i,j;
    for(i = 0; i < ARR_SIZE; i++){
        for(j = 0; j < blocks->size; j++){
            if(are_equal_blocks_s(array[i],blocks[j]))
                array[i].size = 0;
        }
    }

}



struct StaticBlock closest_block_sum_to_s(int x, struct StaticBlock blocks []){
    /*
      Idea is to calculate sum of each block and compare to closest sum we found earlier
   */
    int i,j;
    struct StaticBlock closest_block;
    // Any block has >0 chars, so to make comparing length work
    int closest_block_sum = -1;

    for(i = 0; i < ARR_SIZE; i++){
        int sum = 0;
        for(j = 0; j < blocks[i].size; j++){
            if(blocks[i].size > 0) {
                sum += blocks[i].string[j];
            }
        }

        // Comparing length to given number
        if(abs(closest_block_sum - x) > abs(sum - x) ){
            closest_block_sum = sum;
            closest_block = blocks[i];
        }

    }

    return closest_block;
}

