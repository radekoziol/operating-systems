//
// Created by radekkoziol on 25.03.18.
//


#include <bits/types/FILE.h>
#include <zconf.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <stdbool.h>
#include <signal.h>
#include <wait.h>

void
set_limits(int time_limit, int mem_limit) {

    // Some conditions
    if ((time_limit <= 0) || (mem_limit <= 0)) {
        printf("Those limits: ");
        printf("time: %d, memory: %d", time_limit, mem_limit);
        printf("are impossible!");
        exit(-1);
    }
    struct rlimit lim;

    lim.rlim_cur = (rlim_t) time_limit;
    setrlimit(RLIMIT_CPU, &lim);

    lim.rlim_cur = (rlim_t) mem_limit;
    setrlimit(RLIMIT_AS, &lim);

}


void print_info(char commands[256][256], char *args[256]) {
    // Printing file info
    printf("Executing");
    int c = 0;
    while (commands[c][0] != '\0') {
        printf(" %s", commands[c]);
        printf(" %s |", args[c]);
        c++;
    }
}


void
execute_pipe(char command[256][256], char *args[256], int time_limit, int mem_limit){

    print_info(command,args);


    pid_t child_pid;
    int status, command_s;
    status = command_s = 0;

//    // Creating new process
//    int pipes[2];
//    pipe(pipes);
//    child_pid = vfork();
//
//    if( 0 == child_pid ){
//
//        // Setting limits
//        set_limits(time_limit,mem_limit);
//
//        if(command[0] == '`')
//            _exit(127);
//
//
//        // Running command
//        if(args[1] == NULL)
//            command_s = execlp(command, command, (char *) NULL);
//        else
//            command_s = execvp(command, args);
//
//        if(command_s != 0){
//            printf("Process went wrong!\n");
//            kill(0, SIGTERM);
//        }
//        _exit(127); /* terminate the child  */
//    }
//
//    // this way, the father waits for all the child processes
//    while ( wait(&status) > 0 );

}

int
parse_line(const char file[256], int i, char *command, char args[256]) {

    int j, k;

    // Assuming next char is '|'
    while (file[i] == ' ') i++;

    k = 0;
    // Reading command
    while ((file[i] != ' ') && (file[i] != '\0')) {
        command[k++] = file[i++];
    }

    // Has to end with NULL
    command[k] = '\0';

    if (file[i] == '\0') {
        args[k] = '\0';
        return 0;
    }

    i++;
    j = 0;

    // Now we need to split arguments into args array
    while ((file[i] != '\0') && (file[i] != '|')) {
        if (file[i] != ' ') {
            args[j++] = file[i];
        }
        i++;
    }
    // Last argument
    args[j + 1] = '\0';

    //
    if (file[i] == '|') return i + 1;
    return 0;

}

void
execute_file(char *path, int time_lim, int mem_lim) {

    // Opening file
    FILE *f;
    f = fopen(path, "r");

    if (f == NULL) {
        printf("Error while opening file!\n");
        exit(-1);
    }

    // Command
    char commands[256][256];
    // Arguments
    char *args[256];

    for (int i = 0; i < 256; i++) {
        args[i] = (char *) malloc(256 * sizeof(char));
    }

    // Iterating over each line in file
    // @TODO this loop probably can be done without this bool
    bool beg_char = true;

    // When checking we move pointer to next char - so we need to check 1st time
    while (getc(f) != EOF) {

        if (beg_char)
            fseek(f, -1, SEEK_CUR);

        // Reading line
        char line[256];
        fscanf(f, "%[^\n]", line);

        // Parse line arguments
        int p_n = 0, x = 0;
        while ((x = parse_line(line, x, commands[p_n++], args[p_n])) > 0);
        commands[p_n][0] = '\0';



        // Executing command
        execute_pipe(commands,args,time_lim,mem_lim);

        beg_char = false;
    }

    fclose(f);

}