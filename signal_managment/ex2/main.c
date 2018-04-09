#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <stdbool.h>
#include <memory.h>
#include "utils.c"

#define MAX_CHILD  100

int child_pid[MAX_CHILD];
int child_status[MAX_CHILD];
int child_work[MAX_CHILD];
// Parent allowance for children to execute
bool children_can_run = false;

volatile sig_atomic_t request_num = 0;


int work() {

    sleep(1);

    return 1;
}


void sig_usr2(int signo) {
    char buffer[100];
    sprintf(buffer, "[CHILD] SIGUSR2 received from parent. Executing!\n");
    write(1, buffer, strlen(buffer));
}

void sig_usr1(int signo, siginfo_t *info, void *extra) {
    request_num++;
    char buffer[100];
    sprintf(buffer, "[PARENT] SIGUSR1 received from %d \n", info->si_value.sival_int);
    write(1, buffer, strlen(buffer));
}


int main() {

    int N = 10;
    int M = 5;

    set_arr(N, child_pid, child_status, child_work);

    pid_t pid, ppid;
    // Parent pid
    ppid = getpid();


    struct sigaction action;

    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = &sig_usr1;

    if (sigaction(SIGUSR1, &action, NULL) == -1) {
        perror("sigusr: sigaction");
        return 0;
    }


    for (int i = 0; i < N; ++i) {

        if ((child_pid[i] = fork()) == 0) {

            if (signal(SIGUSR2, sig_usr2) == SIG_ERR)
                printf("Something went wrong!\n");
            if (!children_can_run) {

                union sigval r_val;
                r_val.sival_int = getpid();
                sigqueue(ppid, SIGUSR1, r_val);

                pause();

            }

            printf("Process %d starts\n", getpid());
            int time = work();
            printf("Process %d ends with time %d sec\n", getpid(), time);

            _exit(0);
        } else {

            int status = 0;
            status = wait(&status);
            if((status == -1) && (children_can_run))
                printf("Process went unsuccessfully!\n");
            else if((status != -1) && (children_can_run))
                printf("Process went successfully!\n\n");

            if ((request_num >= M) && (!children_can_run)) {
                children_can_run = true;
                for (int j = 0; j < i; j++) {
                    kill(child_pid[j], SIGUSR2);
                    status = wait(&status);
                    if((status == -1) && (children_can_run))
                        printf("Process went unsuccessfully!\n");
                    else if((status != -1) && (children_can_run))
                        printf("Process went successfully!\n\n");
                }

            }



        }
    }

}
