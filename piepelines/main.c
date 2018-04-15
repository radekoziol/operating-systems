//
// Created by radekkoziol on 10.04.18.
//

#include <zconf.h>
#include <stdio.h>
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

int main() {
//
//    parent_to_child_and_otherwayaround();

    some_command();

    //    printf("child_to_parent\n");
//    child_to_parent();

}

