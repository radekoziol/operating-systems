//
// Created by radekkoziol on 28.02.18.
//
#include "block.h"
#include "library.h"

#include <stdio.h>


#include <stdbool.h>
#include <stdlib.h>
#define SIZE 100


struct Block blocks[SIZE];

void add_block_s(struct Block blocks [], struct Block block){

    for(int i = 0; i < SIZE; i++)
        if(blocks[i].size == 0){
            blocks[i] = block;
            return;
        }

    printf("Block array is full!");

}

void delete_block_s(struct Block array [], struct Block * blocks){

    int i,j;
    for(i = 0; i < SIZE; i++){
        for(j = 0; j < blocks->size; j++){
            if(are_equal_blocks(array[i],blocks[j]))
                array[i].size = 0;
        }
    }

}

struct Block closest_block_sum_to_s(int x, struct Block blocks []){
    /*
      Idea is to calculate sum of each block and compare to closest sum we found earlier
   */
    int i,j;
    struct Block closest_block;
    // Any block has >0 chars, so to make comparing legnth work
    int closest_block_sum = -1;

    for(i = 0; i < SIZE; i++){
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



//void delete_block(struct Block array [] , struct Block blocks []);


void hello(){

    struct Block ex1;
    struct Block ex2;
    struct Block ex3;

    ex1.size = 2;
    char string1 [2];
    string1[0] = 'a';
    string1[1] = 'a';
    ex1.string = string1;

    ex2.size = 3;
    char string2 [3];
    string2[0] = 'b';
    string2[1] = 'b';
    string2[2] = 'b';
    ex2.string = string2;

    ex3.size = 2;
    char string3 [2];
    string3[0] = 'c';
    string3[1] = 'c';
    ex3.string = string3;


    add_block_s(blocks, ex1);
    add_block_s( blocks, ex2);
    add_block_s(blocks, ex2);
    add_block_s(blocks, ex3);
    add_block_s(blocks, ex3);
    add_block_s(blocks, ex3);



//    struct Block blocks2[10];
//
//    add_block_s(blocks2,ex2);
//    add_block_s(blocks2,ex3);
//
//    delete_block_s(blocks,blocks2);
//
//    for(int i = 0; i < 10; i++){
//        printf("%d\n", blocks[i].size);
//    }



    struct Block block2 = closest_block_sum_to_s(197,blocks);


    printf("%c", block2.string[0]);




}