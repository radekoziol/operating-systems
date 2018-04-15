//
// Created by radekkoziol on 18.03.18.
//

#if defined(__linux__) || defined(__MINT__)
# define _GNU_SOURCE /* strptime(), getsubopt() */

#endif

#include <stdio.h>
#include <stdlib.h>
#include "library/utils.c"


#include <zconf.h>
#include <stdio.h>
#include <memory.h>

/*
 * ps aux | grep root | wc -l
 */
void some_command(){

//    char buff[100] = "Hello World\n";

    int fd[2];
    pipe(fd);
    pid_t pid = fork();

    if (pid == 0) { // dziecko
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);
        execlp("wc", "wc","-l", NULL);
    } else if(fork() == 0){ // rodzic
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);
        execlp("grep", "grep","root", NULL);

    }
    else if(fork() == 0){ // rodzic
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);
        execlp("grep", "grep","S", NULL);
    }
    else{
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        execlp("ps","ps", "aux", NULL);
    }



}


int
main(int argc, char **argv) {



//    Example input

    argv[1] = "../file.txt";
    argv[2] = "10";
    argv[3] = "100";
    argc = 3;

    if ((argc == 1) || strcmp(argv[1], "-help") == 0) {
        printf("Arguments are: \n"
               "   path time_limit memory_limit \n");
        exit(0);
    }

    int time_l = (int) strtol(argv[2], NULL, 10);
    int mem_l = (int) strtol(argv[3], NULL, 10);
    // Converting to MB
    mem_l = 1048576*mem_l;

    char* path= argv[1];

    execute_file(path,time_l,mem_l);


    return 0;
}
