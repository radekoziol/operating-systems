#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <memory.h>
#include <wait.h>

static volatile sig_atomic_t got_sigstp_signal = 0;
static volatile sig_atomic_t got_sigint_signal = 0;

void stop_program(int signum) {
    got_sigint_signal = 1;
}

void continue_program(int signum) {
    got_sigstp_signal = 1;
}

int main() {
    
    struct sigaction action,sa;

    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_handler = &stop_program;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return EXIT_FAILURE;
    }

    // Setting handler for stopping
    sigaction (SIGINT, NULL, &action);

    action.sa_handler = &continue_program;
    action.sa_flags = SA_NODEFER;
    sigemptyset(&action.sa_mask);

    // Setting handler for continuing
    sigaction(SIGTSTP, &action, NULL);


    while (1) {

        int status;
        char *args[2];

        // Setting global to 0
        got_sigstp_signal = 0;

        args[0] = "./print_date";        // first arg is the full path to the executable
        args[1] = NULL;             // list of args must be NULL terminated

        if ( fork() == 0 )
            execv( args[0], args ); // child: call execv with the path and the args
        else
            wait( &status );        // parent: wait for the child (not really necessary)


        // Checking if SIGINT was received
        if (got_sigint_signal) {
            got_sigint_signal = 0;
            printf("\nSIGINT received - exiting!\n");
            exit(1);
        }

        if(got_sigstp_signal){
            printf("\nWaiting on:\n CTRL + Z - continue program \n CTRL + C - exiting program...\n");
            got_sigstp_signal = 0;
            pause();
        }

    }


}