#ifndef MEM_LIB_TIME_MANAGMENT_LIBRARY_H
#define MEM_LIB_TIME_MANAGMENT_LIBRARY_H

#include <stdbool.h>
#include "block.h"

void hello(void);


void hello1(void);

void add_block_s(struct Block blocks [], struct Block block);

void add_block_d(struct Block ** array, struct Block block);

void delete_block_d(struct Block ** array, struct Block * blocks);

void delete_block_s(struct Block array [], struct Block * blocks);

struct Block closest_block_sum_to_d(int x, struct Block * array);

struct Block closest_block_sum_to_s(int x, struct Block blocks []);



#endif