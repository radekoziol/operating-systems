#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <stdbool.h>

int k = 0;
int child_pid[10];
bool can_run = false;


void sig_usr2(int signo) {
    printf("Executing!\n");
    if (signo == SIGUSR2)
        sleep(1);
}

void sig_usr1(int signo) {
    if (signo == SIGUSR1)
        k++;
}


int main() {

    int N = 10;
    for (int j = 0; j < N; j++)
        child_pid[j] = 123;
    int c = 0;

    pid_t pid, ppid;
    ppid = getpid();


    if (signal(SIGUSR1, sig_usr1) == SIG_ERR)
        printf("Something went wrong!\n");


    for (int i = 0; i < N; ++i) {
        if ((child_pid[i] = fork()) == 0) {
            if (signal(SIGUSR2, sig_usr2) == SIG_ERR)
                printf("Something went wrong!\n");
            printf("Sending sigusr1 to parent!\n");
            kill(ppid, SIGUSR1);
            pause();
        }else{
            if((i>3)  || (can_run)){
                printf("Allowing kids to execute!\n");
                can_run = true;
                for (int j = 0; j < 10; j++){
                    kill(child_pid[j],SIGUSR2);
                }
            }
        }
    }


    if (getpid() == ppid){
        for (int j = 0; j < N; j++)
            printf("%d,", child_pid[j]);
    }






}