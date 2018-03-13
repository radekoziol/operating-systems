# mem&lib&time_managment

C project that compares dynamically and statically allocated memory - the diffrence in user, system and real time. 
Library contains methods for dealing with (static of dynamic) blocks of chars.
. 

## Getting Started

``` 
usage:
Arguments are: 
 <array size> <block size> <array allocation method (static or dynamic)> 
 <operation 1> <operation2> <num> <operation3>
Possible operations: 
  -create  -  creates array with blocks
  -find_block <num> -  find closest sum of characters in block(ASCII) to given number
  -add_and_delete  -  deletes blocks and then add newly generated
                                 prints this
```
##### Program perform time measurment that's output is in report2.txt
 
More to find in makefiles and in code


### Conclusions

It's always faster no to use dynamic arrays. Bruce Eckel from Thinking in C++:

"
For maximum runtime speed, the storage and lifetime can be determined while the program is being written, by placing the objects on the stack or in static storage. The stack is an area in memory that is used directly by the microprocessor to store data during program execution. Variables on the stack are sometimes called automatic or scoped variables. The static storage area is simply a fixed patch of memory that is allocated before the program begins to run. Using the stack or static storage area places a priority on the speed of storage allocation and release, which can be valuable in some situations.

In case of dynamic memory allocation: 
Because the storage is managed dynamically at runtime, the amount of time required to allocate storage on the heap is significantly longer than the time to create storage on the stack. 
(Creating storage on the stack is often a single microprocessor
instruction to move the stack pointer down, and another to move it
back up.)"
