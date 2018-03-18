//
// Created by radekkoziol on 13.03.18.
//

#include <stdio.h>
#include <stdlib.h>
#include "test/test.c"


int main(int argc, char **argv){


    if( (argv[1] == NULL)  || strcmp(argv[1], "-help" ) == 0 ) {
        printf("Arguments are: \n"
                       " -generate      path num1 num2\n"
                       " -sort          path num1 num2 how\n"
                       " -copy          path1 path2 num1 num2 how\n");
        printf("Description: \n");
        printf(" -generate  -  generates <num1> lines of data with strings "
                       " of length <num2> to file <path> \n");
        printf(" -sort      -  sorts given file <path> that contains "
                       " <num1> lines of string of length <num2>. It can be done with"
                       " library functions <how = 'lib'> or system functions <how = 'sys>.\n");
        printf(" -copy      -  copies <num1> lines of string of length <num2> "
                       "to file <path1>. It can be done with"
                       " library functions <how = 'lib'> or system functions <how = 'sys>.\n");
        exit(0);
    }
    if(argc < 5){
        printf("You did not input enough arguments!\nFor more information write -help\n");
        exit(0);
    }

    if(strcmp(argv[1], "-generate") == 0){
        generate(argv[2], (unsigned int) strtol(argv[3],NULL,0),
                 (unsigned int) strtol(argv[4],NULL,0));
        printf("Generation went successfully!\n");
        exit(0);
    }
    if(strcmp(argv[1], "-sort") == 0){
        if(strcmp(argv[5], "sys") == 0)
            sort_sys(argv[2], (unsigned int) strtol(argv[3], NULL, 0),
                     (unsigned int) strtol(argv[4],NULL,0));

        else
            sort_lib(argv[2], (unsigned int) strtol(argv[3], NULL, 0),
                     (unsigned int) strtol(argv[4],NULL,0));
        printf("Sorting went successfully!\n");
        exit(0);
    }
    if(strcmp(argv[1], "-copy") == 0){
        if(strcmp(argv[6], "sys") == 0)
            copy_sys(argv[2], argv[3], (size_t) (strtol(argv[4],NULL,10) * strtol(argv[5],NULL,10)));
        else
            copy_lib(argv[2], argv[3], (size_t) (strtol(argv[4],NULL,10) * strtol(argv[5],NULL,10)));
        printf("Copying went successfully!\n");
        exit(0);

    }





}