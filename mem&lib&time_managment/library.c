#include "library.h"

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>


struct Block{

    //Actual block
    char**          block;
    //Size
    unsigned int     x,y;

};

struct Block * create_array(int size){

    struct Block* blocks = calloc((size_t) size, sizeof *blocks);
    return blocks;
}

void delete_array(struct Block * array){
    free(array);
}

struct Block * add_block(struct Block * array, int *size_p, struct Block block){

    int it = 0;

    while(it < *size_p){

        //Because calloc initializes so, it consider this as empty
        if(array[it].x == 0){
            array[it] = block;
            break;
        } else
            it++;
    }

    // Array overflow - 2 * size
    if(it == *size_p){
        array = realloc(array, sizeof * array );
        *size_p = *size_p * 2;
        array[it] = block;
    }

    return array;
}


bool are_equal_blocks(struct Block block1, const int size1, struct Block block2, const int size2) {

    if((block1.x != block2.x) || (block1.y != block2.y) )
        return false;
    else
        for(int i = 0; i < size1; i++)
            for(int j = 0; j < size2; j++)
                for(int k = 0; k < size2; k++)
                    if(block1.block[i][k] != block2.block[j][k])
                        return false;


    return true;
}


struct Block * delete_block(struct Block * array, const int *size_a, struct Block * blocks, int size_b){


    for(int i = 0; i < *size_a; i++){
        for(int j = 0; j < size_b; j++){
            if(are_equal_blocks(array[i],*size_a,blocks[j], size_b))
                array[i].x = 0;
        }
    }

    return array;
}



void hello(void) {

    int size = 1;

    struct Block ex1;
    ex1.x = 1;
    ex1.y = 2;

    char **arr = (char **)calloc((size_t) ex1.x, sizeof(char *));
    arr[0] = (char *)calloc((size_t) ex1.y, sizeof(char));
    arr[0][0] = 'x';
//    for (int i=0; i< ex1.x; i++)
//        arr[i] = (char *)calloc((size_t) ex1.y, sizeof(char));
//
//    for (int i = 0; i <  ex1.x; i++)
//        for (int j = 0; j < ex1.y; j++)
//            arr[i][j] = 'x';
//
//
//    ex1.block = arr;

    struct Block * blocks = create_array(size );

    int* size_p = &size;
    blocks = add_block(blocks, size_p, ex1);

    struct Block ex2;
    ex2.y = 3;

    blocks = add_block(blocks, size_p, ex2);


    printf("%d\n", blocks[1].y);

    delete_array(blocks);
}

