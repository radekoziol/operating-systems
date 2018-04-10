#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <stdbool.h>
#include <memory.h>
#include "../ex2/utils.c"

int child_pid;
int parent_pid;
bool can_exit = 0;
// Parent allowance for children to execute
bool children_can_run = false;
// Counter of request sent to parent
volatile sig_atomic_t request_num = 0;
pid_t real_time_sig = -2;


void real_signal_handler(int signo, siginfo_t *info, void *extra) {
    char buffer[100];
    sprintf(buffer, "[PARENT] Received real time signal: %s\n", strsignal(signo));
    write(1, buffer, strlen(buffer));
    real_time_sig = info->si_value.sival_int;
}

void sig_usr2_ch(int signo) {
    char buffer[100];
    sprintf(buffer, "[CHILD]  SIGUSR2 received from parent.\n");
    write(1, buffer, strlen(buffer));
    can_exit = 1;
    exit(EXIT_SUCCESS);
}

void sig_usr1_p(int signo) {
    char buffer[100];
    sprintf(buffer, "[PARENT]  SIGUSR1 received from child.\n");
    write(1, buffer, strlen(buffer));
}


void sig_usr1_ch(int signo) {
    request_num++;
    char buffer[100];
    sprintf(buffer, "[CHILD]  Sending back SIGUSR1 to parent.\n");
    write(1, buffer, strlen(buffer));
    kill(getppid(), SIGUSR1);
}


int main(int argc, char **argv) {

    argc = 2;
    argv[1] = "10";

//    if ((argc == 1) || strcmp(argv[1], "-help") == 0) {
//        printf("Arguments are: \n"
//                       "   child_number request_number \n");
//        exit(0);
//    }
    int L = (int) strtol(argv[1], NULL, 10);


    // Parent pid
    parent_pid = getpid();


    struct sigaction action;

    action.sa_flags = SA_SIGINFO;
//    action.sa_sigaction = &sig_usr1_p;
//
//    if (sigaction(SIGUSR1, &action, NULL) == -1) {
//        perror("sigusr: sigaction");
//        return 0;
//    }

    if (signal(SIGUSR1, sig_usr1_p) == SIG_ERR)
        printf("Something went wrong!\n");

    for (int i = SIGRTMIN; i <= SIGRTMAX; i++) {
        action.sa_sigaction = real_signal_handler;
        if (sigaction(i, &action, NULL) == -1) {
            printf("ER?\n");
            exit(-1);
        }
    }

    sigset_t signal_set;/* sygnały do blokowania */

    if ((child_pid = fork()) == 0) {


        sigset_t newmask;
        sigset_t oldmask;
        sigemptyset(&newmask);
        sigfillset(&newmask);

        sigdelset(&newmask, SIGUSR1);
        sigdelset(&newmask, SIGUSR2);

        sigprocmask(SIG_SETMASK, &newmask, &oldmask);

        struct sigaction act;
        act.sa_flags = SA_SIGINFO;
        sigemptyset(&act.sa_mask);


        if (signal(SIGUSR1, sig_usr1_ch) == SIG_ERR)
            printf("Something went wrong!\n");

        if (signal(SIGUSR2, sig_usr2_ch) == SIG_ERR)
            printf("Something went wrong!\n");

        while(!can_exit);

        _exit(0);

    } else {



        for (int i = 0; i < L; i++) {
            printf("[PARENT] SENDING SIGUSR1 to child!\n");
            kill(child_pid, SIGUSR1);
            pause();
        }

        printf("[PARENT] SENDING SIGUSR2 to child!\n");
        kill(child_pid, SIGUSR2);

        waitpid(child_pid, NULL, 0);
        exit(EXIT_SUCCESS);

    }


}
