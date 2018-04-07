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
#include "time_m.c"

void
set_limits( int time_limit, int mem_limit) {

    // Some conditions
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
execute_command(char *command, char *args[256], int time_limit, int mem_limit){

    pid_t child_pid;
    int status, command_s;
    status = command_s = 0;

    // Creating new process
    int pipes[2];
    pipe(pipes);
    child_pid = vfork();

    if( 0 == child_pid ){

        // Setting limits
        set_limits(time_limit,mem_limit);

        if(command[0] == '`')
            _exit(127);
                    
        // Running command
        if(args[1] == NULL)
            command_s = execlp(command, command, (char *) NULL);
        else
            command_s = execvp(command, args);

        if(command_s != 0){
            printf("Process went wrong!\n");
            kill(0, SIGTERM);
        }
        _exit(127); /* terminate the child  */
    }

    // this way, the father waits for all the child processes
    while ( wait(&status) > 0 );

    print_results(measure_time());

}

void
parse_line(FILE *f, char *command, char *args[256]){

    char file[256];
    int i,j,k;

    for(i = 0; i < 256; i++)
        file[i] = '\0';

    // Reading line
    fscanf(f, "%[^\n]", file);

    // Reading command
    i = 0;
    while ((file[i] != ' ') && (file[i] != '\0')) {
        command[i] = file[i];
        i++;
    }
    // Has to end with NULL
    command[i] = '\0';
    // According to execvp syntax
    args[0] = command;

    if(file[i] == '\0'){
        args[1] = '\0';
        return;
    }

    i++;
    j = 1;
    k = 0;

    // Now we need to split arguments into args array
    while(file[i] != '\0'){

        if(file[i] != ' ') {
            args[j][k] = file[i];
            k++;
        }
        else{
            args[j][k] = '\0';
            k = 0;
            j++;
        }
        i++;
    }

    // Last argument
    args[j][k] = '\0';
    args[j+1] = NULL;

}

void
execute_file(char * path, int time_lim, int mem_lim){

    // Opening file
    FILE *f;
    f = fopen(path, "r");

    if (f == NULL) {
        printf("Error while opening file!\n");
        exit(-1);
    }

    // Command
    char command[256];
    // Arguments
    char *args[256];

    for (int i=0; i<256; i++)
        args[i] = (char *)malloc(256 * sizeof(char));

    // Iterating over each line in file
    // @TODO this loop probably can be done without this bool
    bool beg_char = true;

    // When checking we move pointer to next char - so we need to check 1st time
    while (getc(f) != EOF){

        if(beg_char)
            fseek(f,-1,SEEK_CUR);

        // Parse line arguments
        parse_line(f,command,args);

        // Printing file info
        printf("Executing ");
        int i = 0;
        while(args[i] != NULL) {
            printf(" %s", args[i++]);
        }
        printf("\n");

        // Executing command
        execute_command(command,args,time_lim,mem_lim);

        beg_char = false;
    }

    fclose(f);

}