#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <memory.h>
#include <wait.h>

static volatile sig_atomic_t got_sigstp_signal = 0;
static volatile sig_atomic_t got_sigint_signal = 0;


void my_handler(int signum)
{
    if (signum == SIGUSR1)
    {
        printf("Received SIGUSR1!\n");
    }
}

int main() {
    int N = 10;


    for (int i = 0; i < N; ++i) {
        int pid = fork();
        if(pid < 0){
            exit(EXIT_FAILURE);
        }
        else if (pid > 0){
            // Parent
        }
        else{
            // Child
            printf("Child here!\n");
            exit(EXIT_SUCCESS);
        }
    }

    for (int i = 0; i < N; ++i) {
        int status;
        pid_t pid = wait(&status); // kids could be ready in any order
    }


    signal(SIGUSR1, my_handler);

    kill(getpid(), SIGUSR1);


}