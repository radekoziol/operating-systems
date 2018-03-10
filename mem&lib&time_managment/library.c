#include "library.h"

#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>


struct Block{

    //Actual string
    char *       string;
    //Size
    unsigned int size;

};

struct Block * create_array(){

    struct Block* blocks = malloc(1 * sizeof *(blocks));

    // On first element we store size of array blocks
    blocks[0].size = (unsigned int) 1;

    return blocks;
}

void delete_array(struct Block * array){
    free(array);
}

void add_block(struct Block ** array, struct Block block){

    // If string is empty it is not added
    if(block.string == NULL)
        return;

    // Iterating over array to find any empty cell
    int it = 0;

    struct Block * temp_array = *array;
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

        struct Block* blocks  = (struct Block*)realloc(*array, (2 * size * sizeof(struct Block)));

        if (blocks == NULL)
            printf("Cannot allocate more memory.\n");
        else {
            blocks[it] = block;
            blocks->size = (unsigned int) (size * 2);
            *array = blocks;

        }

    }

}

struct Block closest_block_sum_to(int x, struct Block * array){

    /*
        Idea is to calculate sum of each block and compare to closest sum we found earlier
     */
    int size = array->size;
    int i,j;
    struct Block closest_block;
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


bool are_equal_blocks(struct Block block1, struct Block block2) {

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


void delete_block(struct Block ** array, struct Block * blocks){

    struct Block * temp_array = *array;
    // Size of allocated array
    int size = temp_array[0].size;

    // We check each block with to_delete_array blocks [o(n^2)]
    for(int i = 1; i < size; i++){
        for(int j = 1; j < blocks->size; j++){
            if(are_equal_blocks(temp_array[i],blocks[j]))
                temp_array[i].size = 0;

        }
    }

    *array = temp_array;
}



void hello(void) {


    struct Block ex1;
    struct Block ex2;
    struct Block ex3;

    ex1.size = 2;
    ex1.string = (char *)calloc((size_t) ex1.size, sizeof(char *));

    ex1.string[0] = 'a';
    ex1.string[1] = 'a';

    ex2.size = 2;
    ex2.string = (char *)calloc((size_t) ex2.size, sizeof(char *));

    ex2.string[0] = 'b';
    ex2.string[1] = 'b';

    ex3.size = 100;
    ex3.string = (char *)calloc((size_t) ex3.size, sizeof(char *));

    ex3.string[0] = 'c';
    ex3.string[1] = 'c';

    struct Block * blocks = create_array();


    add_block(&blocks, ex1);
    add_block(&blocks, ex2);
    add_block(&blocks, ex2);
    add_block(&blocks, ex3);
    add_block(&blocks, ex3);
    add_block(&blocks, ex3);


    struct Block block2 = closest_block_sum_to(197,blocks);

    printf("%c", block2.string[1]);



    delete_array(blocks);


}


