#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

int c = 0;

int c_2 = 0;

void continue_pr(int signum) {
    printf("\nExiting!\n");
    exit(1);
}

void stop_pr(int signum) {

    if(c_2 != 0)
        printf("\nContinuing!\n");
    else{
        c_2++;
        printf("\nWaiting on:\n CTRL + Z - continue program \n CTRL + C - exiting program...\n");
        raise(SIGINT);
    }
}

void handle_sig(int signum) {

    c++;
    printf("Counter: %d\n", c);

}
void au(int sig_no) {
    printf("Otrzymale signal %d.\n", sig_no);
}


int main() {

    signal(SIGTSTP, stop_pr);
    signal(SIGINT, continue_pr);
//
    while (1) {
        time_t rawtime;
        struct tm * timeinfo;

        time ( &rawtime );
        timeinfo = localtime ( &rawtime );
        printf ( "Current local time and date: %s", asctime (timeinfo) );
        sleep(1);
    }

//    signal(SIGUSR1,handle_sig);
//
//
//    int father_pid = getpid();
//    int child_pid = fork();
//
//    while (1) {
//        kill(father_pid,SIGUSR1);
//        sleep(1);
//    }

//    raise(SIGUSR1);

    return (0);
}
