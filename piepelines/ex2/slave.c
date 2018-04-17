//
// Created by radekkoziol on 17.04.18.
//

#include <zconf.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <memory.h>

#define MAX_BUF 1024

int
main(int argc, char **argv) {

//    Example input
//    argv[1] = "/tmp/myfifo";
//    argv[2] = "5";

    // No real input control
    const char * path = argv[1];
    const int N = (int) strtol(argv[2], NULL, 10);

    int fd;

    // Opening fifo
    fd = open(path, O_WRONLY);
    FILE *date_output = NULL;

    dup2(fd,STDOUT_FILENO);

    for(int i = 1; i <= N; i ++){

        char buffer [MAX_BUF];
        char message[MAX_BUF];

        int x = getpid();
        int length = snprintf( NULL, 0, "%d", x );
        char* str = malloc((size_t) (length + 1));
        snprintf(str, (size_t) (length + 1), "%d", x );

        date_output = popen("date", "r");

        int c = fgetc(date_output);
        int buf_c = 0;
        while (c != EOF) {
            buffer[buf_c++] = (char) c;
            c = fgetc(date_output);
        }
        buffer[buf_c] = '\0';

        sprintf(message, "%s%s\n", buffer, str);

        write(fd, message, strlen(message));

        free(str);
        sleep(2);
    }

    close(fd);
    pclose(date_output);



    return 0;

}