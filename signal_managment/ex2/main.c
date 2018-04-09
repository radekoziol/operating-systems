#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <stdbool.h>
#include <memory.h>

#define MAX_CHILD  100

int child_pid[MAX_CHILD];
int child_status[MAX_CHILD];
int child_work[MAX_CHILD];
// Parent allowance for children to execute
bool children_can_run = false;

volatile sig_atomic_t request_num = 0;

int work();

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
    for (int j = 0; j < N; j++)
        child_pid[j] = 123;
    int c = 0;

    pid_t pid, ppid,wpid;
    ppid = getpid();


    struct sigaction action;

    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = &sig_usr1;

    if (sigaction(SIGUSR1, &action, NULL) == -1) {
        perror("sigusr: sigaction");
        return 0;
    }


    for (int i = 0; i < N; ++i) {
        int status;

        if ((child_pid[i] = fork()) == 0) {

            if (signal(SIGUSR2, sig_usr2) == SIG_ERR)
                printf("Something went wrong!\n");
            if(!children_can_run){

                union sigval r_val;
                r_val.sival_int = getpid();
                sigqueue(ppid, SIGUSR1, r_val);

                pause();
                sleep(1);

            }else{
                sleep(1);
//                int time = work();
            }

            _exit(0);
        }else{
            int status;
            wait(&status);

            if((request_num>=M)  && (!children_can_run)){
                children_can_run = true;
                for (int j = 0; j < i; j++){
                    kill(child_pid[j],SIGUSR2);
                    wait(&status);
                }

            }

        }
    }


    if (getpid() == ppid){
        for (int j = 0; j < N; j++)
            printf("%d,", child_pid[j]);

        printf("\n%d\n", request_num);
    }






}

//int work() {
//    sprintf("start sleep\n");
//    fflush(stdout);
//    sleep(5);   //sleep 1s
//    printf("stop sleep\n");
//    return 0;
//}