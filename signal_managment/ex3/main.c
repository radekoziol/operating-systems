#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <stdbool.h>
#include <memory.h>
#include "../ex2/utils.c"

int child_pid;
bool can_finish = 0;
// Default values
int first_signal = SIGUSR1;
int second_signal = SIGUSR2;

int child_c = 0;
int parent_c = 0;


void sig_usr2_ch(int signo, siginfo_t *info, void *context) {
    char buffer[100];
    sprintf(buffer, "[CHILD]  %s received from parent.\n", strsignal(second_signal));
    write(1, buffer, strlen(buffer));
    can_finish = 1;
    exit(EXIT_SUCCESS);
}

void sig_usr1_ch(int signo, siginfo_t *info, void *context) {
    child_c++;
    char buffer[100];
    sprintf(buffer, "[CHILD]  Sending back signal %s to parent\n", strsignal(first_signal));
    write(1, buffer, strlen(buffer));
    kill(getppid(), SIGUSR1);
}

void sig_usr1_p(int signo, siginfo_t *info, void *context) {
    parent_c++;
    char buffer[100];
    sprintf(buffer, "[PARENT] Received signal %s from child.\n", strsignal(first_signal));
    write(1, buffer, strlen(buffer));
}

void sig_int_p(int signo, siginfo_t *info, void *context) {
    char buffer[100];
    sprintf(buffer, "[PARENT] %s received.\n", strsignal(first_signal));
    write(1, buffer, strlen(buffer));
    exit(-1);
}


int main(int argc, char **argv) {


//    Example input
//    argc = 2;
//    argv[1] = "10";
//    argv[2] = "1";


    if ((argc == 1) || strcmp(argv[1], "-help") == 0) {
        printf("Arguments are: \n"
                       "   signal_num type<1,2,3> \n");
        exit(0);
    }

    int L = (int) strtol(argv[1], NULL, 10);
    int type = (int) strtol(argv[2], NULL, 10);

    if((type >= 4) || (type <= 0)){
        printf("Type argument can have value of 1,2 or 3!\n"
               "For more information use option -help \n");
    }

    if(type == 3){
        first_signal = SIGRTMIN + 2;
        second_signal = SIGRTMAX - 2;
    }

    if ((child_pid = fork()) == 0) {

        // Unblocking signals
        sigset_t newmask;
        sigset_t oldmask;
        sigemptyset(&newmask);
        sigfillset(&newmask);

        sigdelset(&newmask, first_signal);
        sigdelset(&newmask, second_signal);

        sigprocmask(SIG_SETMASK, &newmask, &oldmask);

        // Setting handlers
        struct sigaction act;
        act.sa_flags = SA_SIGINFO;
        sigemptyset(&act.sa_mask);

        act.sa_sigaction = sig_usr1_ch;
        if (sigaction(first_signal, &act, NULL) == -1) {
            printf("[ERROR] Can't catch signal %d.\n", first_signal);
        }

        act.sa_sigaction = sig_usr2_ch;
        if (sigaction(second_signal, &act, NULL) == -1) {
            printf("[ERROR] Can't catch signal %d.\n", second_signal);
        }

        while(!can_finish);

        _exit(0);

    } else {

        // Setting handlers for parent
        struct sigaction act;
        act.sa_flags = SA_SIGINFO;
        sigemptyset(&act.sa_mask);

        act.sa_sigaction = sig_usr1_p;
        if (sigaction(first_signal, &act, NULL) == -1) {
            printf("[ERROR] Can't catch signal %d.\n", first_signal);
        }
        act.sa_sigaction = sig_int_p;
        if (sigaction(SIGINT, &act, NULL) == -1) {
            printf("[ERROR] Can't catch signal %d.\n", SIGINT);
        }

        for (int i = 0; i < L; i++) {
            printf("[PARENT] Sending %s to child!\n",strsignal(first_signal));
            kill(child_pid, first_signal);
            if(type == 2)
                pause();
        }

        int status;
        wait(&status);
        printf("[PARENT] Sending %s to child!\n",strsignal(second_signal));
        kill(child_pid, second_signal);

        waitpid(child_pid, NULL, 0);
        exit(EXIT_SUCCESS);

    }


}