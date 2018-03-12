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

bool are_equal_blocks_d(struct DynamicBlock block1, struct DynamicBlock block2) {

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


struct DynamicBlock * create_array_d(int size){

    struct DynamicBlock* blocks = malloc(size * sizeof *(blocks));

    // On first element we store size of array blocks
    blocks->size = (unsigned int) size;

    return blocks;
}

void delete_array_d(struct DynamicBlock * array){
    free(array);
}

void add_block_d(struct DynamicBlock ** array, struct DynamicBlock block){

    // If string is empty it is not added
    if(block.string == NULL)
        return;

    // Iterating over array to find any empty cell
    int it = 0;

    struct DynamicBlock * temp_array = *array;
    // Allocated size of array
    int size = temp_array->size;

    while(it < size){
        //Because calloc initializes so, it consider this as empty
        if(temp_array[it].size == 0 ){
            temp_array[it] = block;
            break;
        } else
            it++;
    }

    // Array overflow - we need realloc 2 * size
    if(it == size){

        struct DynamicBlock* blocks  =
                (struct DynamicBlock*)realloc(*array, (2 * size * sizeof(struct DynamicBlock)));

        if (blocks == NULL)
            printf("Cannot allocate more memory.\n");
        else {
            blocks[it] = block;
            blocks->size = (unsigned int) (size * 2);
            *array = blocks;

        }

    }



}

void add_blocks_d(struct DynamicBlock ** array, struct DynamicBlock* blocks){

    for(int i = 0; i < blocks->size; i++)
        add_block_d(array,blocks[i]);


}


void delete_blocks_d(struct DynamicBlock ** array, struct DynamicBlock * blocks){

    struct DynamicBlock * temp_array = *array;
    // Size of allocated array
    int size = temp_array->size;

    // We check each block with to_delete_array blocks [o(n^2)]
    for(int i = 1; i < size; i++){
        for(int j = 0; j < blocks->size; j++){
            if(are_equal_blocks_d(temp_array[i],blocks[j])){}
                temp_array[i].size = 0;

        }
    }

    *array = temp_array;
}


struct DynamicBlock closest_block_sum_to_d(int x, struct DynamicBlock * array){

    /*
        Idea is to calculate sum of each block and compare to closest sum we found earlier
     */
    int size = array->size;
    int i,j;
    struct DynamicBlock closest_block;
    // Any block has >0 chars, so to make loop work
    int closest_block_sum = -1;

    for(i = 1; i < size; i++){
        int sum = 0;
        for(j = 0; j < array[i].size; j++){
            sum += array[i].string[j];
        }

        // Comparing length to given number
        if(abs(closest_block_sum - x) > abs(sum - x) ){
            closest_block_sum = sum;
            closest_block = array[i];
        }

    }

    return closest_block;
}


