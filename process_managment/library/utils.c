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

    child_pid = vfork();

    struct rusage usage;
    struct timeval user_start, user_end, system_start, system_end;

    if( 0 == child_pid ){

        printf("Executing ");
        printf(command);
        int i = 1;
        while(args[i] != NULL)
            printf(args[i++]);
        printf("\n");

        set_limits(time_limit,mem_limit);

        command_s = execvp(command, args);

        if(command_s == -1){
            printf("Process went wrong!\n");
            exit(-1);
        }
        _exit(127); /* terminate the child  */
    }

    // this way, the father waits for all the child processes
    while ( wait(&status) > 0 );
    printf("\n");

    getrusage(RUSAGE_CHILDREN, &usage);
    user_end = usage.ru_utime;
    system_end = usage.ru_stime;


    double system_time = parse_to_double(system_end);

    double user_time = parse_to_double(user_end);


    double * result = calloc(3, sizeof(double));
    result[0] = user_time;
    result[1] = system_time;

    print_results(result);

}

void
parse_line(FILE *f, char *command, char *args[256]){

    char file [256];

    int i,j,k;

    fscanf(f, "%[^\n]", file);

    i = 0;
    while ((file[i] != ' ') && (i < 256)) {
        command[i] = file[i];
        i++;
    }
    command[i] = NULL;
    i++;

    j = 1;
    args[0] = command;
    k = 0;
    while(file[i] != NULL){

        if(file[i] != ' ') {
            args[j][k] = file[i];
            k++;
        }
        else{
            args[j][k] = NULL;
            k = 0;
            j++;
        }
        i++;
    }

    args[j][k] = NULL;
    args[j+1] = NULL;

}

void
execute_file(char * path, int time_lim, int mem_lim){

    FILE *f;
    f = fopen(path, "r");

    if (f == NULL) {
        printf("Error while opening file!");
        exit(-1);
    }


    char command[256];
    char *args[256];

    for (int i=0; i<256; i++)
        args[i] = (char *)malloc(256 * sizeof(char));

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