//
// Created by radekkoziol on 25.03.18.
//


#include <bits/types/FILE.h>
#include <zconf.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <wait.h>
#include <stdbool.h>

void
set_limits( int time_limit, int mem_limit) {

    if((time_limit <= 0) || (mem_limit <= 0)){
        printf("Those limits: ");
        printf("time: %d, memory: %d", time_limit,mem_limit);
        printf("are impossible!");
        exit(-1);
    }

    struct rlimit lim;

    lim.rlim_cur = (rlim_t) time_limit;
    setrlimit (RLIMIT_CPU, &lim);

    lim.rlim_cur = (rlim_t) mem_limit;
    setrlimit (RLIMIT_AS, &lim);

}

void
execute_command(char *command, char *args, int time_limit, int mem_limit){

    pid_t child_pid;
    int status, command_s;
    status = command_s = 0;

    child_pid = vfork();

    if( 0 == child_pid ){

        printf("Executing ");
        printf(command);
        printf(args);
        printf("\n");

        set_limits(time_limit,mem_limit);

        if(args[0] != NULL)
            command_s = execlp(command, command, args, (char *) NULL);
        else
            command_s = execlp(command, command, (char *) NULL);

        if(command_s == -1){
            printf("Process went wrong!\n");
            exit(-1);
        }
        _exit(127); /* terminate the child  */
    }

    // this way, the father waits for all the child processes
    while ( wait(&status) > 0 );
    printf("\n");

}

void
parse_line(FILE *f, char *command, char *args){

    char file [256];

    int i;
    for (i = 0; i < 256; i++) {
        file[i] = command[i] = args[i] = NULL;
    }

    fscanf(f, "%[^\n]", file);


    i = 0;
    while ((file[i] != ' ') && (i < 256)) {
        command[i] = file[i];
        i++;
    }
    command[i] = NULL;

    i++;
    int l = 0;

    while ((i < 256) && (file[i] != NULL)) {
        args[l++] = file[i++];
    }
    args[i] = NULL;

}

void
execute_file(char * path, int time_lim, int mem_lim){

    // Converting to MB
    mem_lim = 1048576*mem_lim;

    FILE *f;
    f = fopen(path, "r");

    if (f == NULL) {
        printf("Error while opening file!");
        exit(-1);
    }


    char command[256];
    char args[256];

    bool beg_char = true;

    while (getc(f) != EOF){

        if(beg_char)
            fseek(f,-1,SEEK_CUR);

        parse_line(f,command,args);

        execute_command(command,args,time_lim,mem_lim);

        beg_char = false;
    }

    fclose(f);

}