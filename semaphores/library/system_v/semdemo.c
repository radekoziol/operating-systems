#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/sem.h>

void error_handler(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

int main(int argc, const char **argv)
{
    if (argc != 1)
    {
        fprintf(stderr, "Usage: %s <no arguments>\n", argv[0]);
        return EXIT_FAILURE;
    }

    int i, sem;
    struct sembuf u = {0, 1, 0};
    struct sembuf d = {0, -1, 0};
    sem = semget(IPC_PRIVATE, 1, 0600);
    semctl(sem, 0, SETVAL, 1);

    if (!fork())
    {
        for (i = 0; i < 10; i++)
        {
            if (semop(sem, &d, 1) == -1)
                error_handler("main | semop [d - father]\n");
            if (write(STDOUT_FILENO, "hello\n", 7) == -1)
                error_handler("main | write [hello]\n");
            if (semop(sem, &u, 1) == -1)
                error_handler("main | semop [u - father]\n");
        }
    } else {
        for (i = 0; i < 10; i++)
        {
            if (semop(sem, &d, 1) == -1)
                error_handler("main | semop [d - child]\n");
            if (write(STDOUT_FILENO, "world\n", 7) == -1)
                error_handler("main | write [world]\n");
            if (semop(sem, &u, 1) == -1)
                error_handler("main | semop [u - child]\n");
        }

        //semctl(sem, 0, IPC_RMID);
    }

    return EXIT_SUCCESS;
}