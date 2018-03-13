//
// Created by radekkoziol on 06.03.18.
//
#include "test (ex 2)/test.c"

int main(int argc, char **argv){

    if( (argv[1] == NULL)  || strcmp(argv[1], "-help" ) == 0 ) {
        printf("Arguments are: \n <array size> <block size> "
                       "<array allocation method (static or dynamic)> "
                       "<operation 1> " "<operation2> <num> " "<operation3>\n");
        printf("Possible operations: \n");
        printf("  -create  -  creates array with blocks\n");
        printf("  -find_block <num> -  find closest sum of characters in block(ASCII) to given number\n");
        printf("  -add_and_delete  -  deletes blocks and then add newly generated\n");
        exit(0);
    }
    if(argc < 5){
        printf("You did not input enough arguments!\nFor more information write -help\n");
        exit(0);
    }

    char *ptr;
    int ret;

    ret = (int) strtol(argv[1], &ptr, 10);
    unsigned int array_size = (unsigned int) ret;
    if(ret == 0 ){
        printf("Something's wrong with your first argument!");
    }

    ret = (int) strtol(argv[2], &ptr, 10);
    unsigned int block_size = (unsigned int) ret;
    if(ret == 0 ){
        printf("Something's wrong with your second argument!");
    }

    char *allocation = argv[3];


    if(strcmp(allocation,"dynamic") == 0 || strcmp(allocation,"static") == 0) {
        struct DynamicBlock *blocks = create_array_d(array_size);

        printf("Blocks array was successfully allocated!\n");

        struct DynamicBlock *add_blocks = generate_blocks_array(array_size, block_size);
        add_blocks_d(&blocks, add_blocks);

        free(add_blocks);
        printf("Blocks were successfully added!\n");

        if (strcmp(argv[5] , "-find_block") == 0) {

            ret = (int) strtol(argv[6], &ptr, 10);
            if(ret == 0 ){
                printf("Something's wrong with your fifth argument!");
            }

            struct DynamicBlock block = closest_block_sum_to_d(ret,blocks);

            printf("Closet block to %d:\n", ret);
            int sum = 0;
            for(int i = 0; i < block.size; i++){
                printf("%c", block.string[i]);
                sum += block.string[i];
            }
            printf(" with block sum = %d", sum);
            printf("\n");

        }

        if (strcmp(argv[7], "-add_and_delete") == 0) {

            struct DynamicBlock *test_blocks = generate_blocks_array(array_size, block_size);

            delete_blocks_d(&blocks, test_blocks);

            add_blocks_d(&blocks, test_blocks);

            free(test_blocks);

            printf("Adding and deleting went successfully!\n");
        }


        free(blocks);
    }




    printf("\n");
    printf("Now some test will be performed!");


    if (freopen("../report2.txt", "w", stdout) == NULL)
    {
        perror("freopen() failed");
        return EXIT_FAILURE;
    }

    test();

    fclose(stdout);






}