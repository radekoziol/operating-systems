#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <stdbool.h>
#include <memory.h>
#include <bits/types/siginfo_t.h>
#include "utils.c"

#define MAX_CHILD  100

int child_pid[MAX_CHILD];
// Parent allowance for children to execute
bool children_can_run = false;
// Counter of request sent to parent
volatile sig_atomic_t request_num = 0;
pid_t real_time_sig  = -2;


void real_signal_handler(int signo, siginfo_t *info, void *extra) {
    char buffer[100];
    sprintf(buffer, "[PARENT] Received real time signal: %s\n", strsignal(signo));
    write(1, buffer, strlen(buffer));
    real_time_sig = info->si_value.sival_int;
}

void sig_usr2(int signo) {
    char buffer[100];
    sprintf(buffer, "[CHILD]  SIGUSR2 received from parent. Executing!\n");
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

    for (int j = 0; j < N; j++) {
        child_pid[j] = -10;
    }

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

    for (int i = SIGRTMIN; i <= SIGRTMAX; i++) {
        action.sa_sigaction = real_signal_handler;
        if (sigaction(i, &action, NULL) == -1) {
            printf("ER?\n");
            exit(-1);
        }
    }


    for (int i = 0; i < N; ++i) {

        printf("%d\n",i);
        if ((child_pid[i] = fork()) == 0) {

            if (signal(SIGUSR2, sig_usr2) == SIG_ERR)
                printf("Something went wrong!\n");
            if (!children_can_run) {

                union sigval r_val;
                r_val.sival_int = getpid();
                sigqueue(ppid, SIGUSR1, r_val);

                pause();

            }

            printf("[PARENT] Process %d starts\n", getpid());
            int time = work();

            union sigval r_val;
            r_val.sival_int = getpid();
//            sigqueue(ppid, get_random_signal(), r_val);
            printf("[PARENT] Process %d ends with time %d sec\n", getpid(), time);

            _exit(0);

        } else{


            int status = 0;
            status = wait(&status);

            if(children_can_run)
                raise(get_random_signal());

            
            if((status == -1) && (children_can_run))
                printf("[PARENT] Process went unsuccessfully!\n");
            else if((status != -1) && (children_can_run))
                printf("[PARENT] Process went successfully!\n\n");

            if ((request_num >= M) && (!children_can_run)) {
                children_can_run = true;
                for (int j = 0; j < i; j++) {
                    kill(child_pid[j], SIGUSR2);
                    status = wait(&status);
                    raise(get_random_signal());
                    if((status == -1) && (children_can_run))
                        printf("[PARENT] Process went unsuccessfully!\n");
                    else if((status != -1) && (children_can_run))
                        printf("[PARENT] Process went successfully!\n\n");
                }

            }



        }
    }

}
