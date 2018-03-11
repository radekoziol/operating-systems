//
// Created by radekkoziol on 28.02.18.
//

#include "library.h"

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include "block.h"

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


struct DynamicBlock * create_array_d(){

    struct DynamicBlock* blocks = malloc(1 * sizeof *(blocks));

    // On first element we store size of array blocks
    blocks[0].size = (unsigned int) 1;

    return blocks;
}

void delete_array_d(struct DynamicBlock * array){
    free(array);
}

void add_blocks_d(struct DynamicBlock ** array, struct DynamicBlock* blocks){

    for(int i = 0; i < blocks->size; i++)
        add_block_d(array,blocks[i]);
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
        if(temp_array[it].size == 0){
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




void delete_blocks_d(struct DynamicBlock ** array, struct DynamicBlock * blocks){

    struct DynamicBlock * temp_array = *array;
    // Size of allocated array
    int size = temp_array[0].size;

    // We check each block with to_delete_array blocks [o(n^2)]
    for(int i = 1; i < size; i++){
        for(int j = 1; j < blocks->size; j++){
            if(are_equal_blocks_d(temp_array[i],blocks[j]))
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

void hello1(void) {


//    struct Block ex1;
//    struct Block ex2;
//    struct Block ex3;
//
//    ex1.size = 2;
//    ex1.string = (char *)calloc((size_t) ex1.size, sizeof(char *));
//
//    ex1.string[0] = 'a';
//    ex1.string[1] = 'a';
//
//    ex2.size = 2;
//    ex2.string = (char *)calloc((size_t) ex2.size, sizeof(char *));
//
//    ex2.string[0] = 'b';
//    ex2.string[1] = 'b';
//
//    ex3.size = 100;
//    ex3.string = (char *)calloc((size_t) ex3.size, sizeof(char *));
//
//    ex3.string[0] = 'c';
//    ex3.string[1] = 'c';
//
//    struct Block * blocks = create_array();
//
//
//    add_block_d(&blocks, ex1);
//    add_block_d(&blocks, ex2);
//    add_block_d(&blocks, ex2);
//    add_block_d(&blocks, ex3);
//    add_block_d(&blocks, ex3);
//    add_block_d(&blocks, ex3);
//
//
//    struct Block block2 = closest_block_sum_to_d(197,blocks);
//
//    printf("%c", block2.string[1]);
//
//
//
//    delete_array(blocks);


}


