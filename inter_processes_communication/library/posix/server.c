//
// Created by radekkoziol on 17.04.18.
//

#include <mqueue.h>

#include <stdio.h>
#include <memory.h>
#include <bits/types/sig_atomic_t.h>
#include <signal.h>
#include <stdlib.h>
#include "utils.c"
#include "../utils.c"
#include "posix.h"
#define SERVER_NAME "/test_queue"


static volatile sig_atomic_t got_sigint_signal = 0;

int id = 0;
const char *client_id[MSGTXTLEN];

void send_msg(const char *q_name, char *message) {

    mqd_t s_mqd;

    if ((s_mqd = mq_open(q_name, O_WRONLY)) == -1) {
        perror("mq_open() error");
        exit(-1);
    }
    printf("Server queue successfully opened!\n");

    char msg[1024];
    sprintf(msg, "%s", message);

    if (mq_send(s_mqd, msg, strlen(msg), 1) >= 0) {
        printf("Mssg :%s: send successfully\n",msg);
    } else {
        perror("mq_open() error");
        exit(-1);
    }

    mq_close(s_mqd);

}

void stop_program(int signum) {
    got_sigint_signal = 1;
}

int server_up() {

    // Setting handler for stopping
    struct sigaction action, sa;

    memset(&sa, 0, sizeof(struct sigaction));
    sa.sa_handler = &stop_program;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return EXIT_FAILURE;
    }
    sigaction(SIGINT, NULL, &action);

    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = MAX_MSG;
    attr.mq_msgsize = MSG_SIZE;
    attr.mq_curmsgs = 0;

    mqd_t mqd;

    if ((mqd = mq_open(SERVER_NAME, O_CREAT | O_RDONLY, 0644, &attr)) == -1) {
        perror("mq_open() error");
        exit(-1);
    }

    return mqd;
}

void server_down(mqd_t mqd) {
    /* cleanup */
    mq_unlink(SERVER_NAME);
    mq_close(mqd);
    exit(0);
}

int extract_id(char msg[1024]) {

    int it = 0;
    while (msg[it] != ':')
        it++;
    it++;

    return msg[it] - '0';
}

int extract_operation_id(char msg[1024]) {

    int it = 0;
    while (msg[it] != ':')
        it++;
    it++;
    while (msg[it] != ':')
        it++;
    it++;

    return msg[it] - '0';
}


int main() {

    mqd_t mqd = server_up();

    struct mq_attr attr;
    printf("Queue successfully created with following attributes: \n");
    mq_getattr(mqd, &attr);
    printf("max #msgs = %ld,max #bytes/msg = %ld,#currently on queue = %ld\n",
           attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);

    // Sharing server id
    // Open file in write mode
    FILE *fp = fopen("../server_id.txt", "w+");

    // If file opened successfully, then write the string to file
    if (fp) {
        fputs(SERVER_NAME, fp);
    } else {
        printf("Failed to open the file\n");
    }
    // Close the file
    fclose(fp);

    int type;
    while (1) {

        // Exiting program
        if (got_sigint_signal) {
            printf("\nExiting\n");
            server_down(mqd);
        }

        char msg[MSG_SIZE];
        if (mq_receive(mqd, msg, sizeof(msg), NULL) >= 0) {


            type = extract_type(msg);

            // Saving id of client before fork
            if (type == 1) {
                client_id[id] = extract_name(msg);
            }
            if (fork() == 0) {
                if ((type == 1) && (in_id_format(msg))) {
                    printf("Received id request: %s\n", msg);
                    printf("Sending identifier %d\n", id);
                    char id_s[10];
                    sprintf(id_s,"%d",id);
                    send_msg(client_id[id],id_s);

                } else if ((type > 1) && type <= 4 && (in_operation_format(msg))) {
                    printf("Received operation request %s\n", msg);

                    int input_id = extract_id(msg);
                    int operation_id = extract_operation_id(msg);
                    parse_to_operation(msg);

                    if (operation_id == 5) {
                        printf("Ending program!\n");
                        kill(getppid(), SIGINT);
                    }

                    printf("Sending back to %s!\n", client_id[input_id]);

                    if (input_id != -1) {
                        if (client_id[input_id] != NULL) {
                            printf("Starting calculation!\n");
                            calculate(msg, operation_id);
                            printf("Sending back results! %s\n", msg);
                            send_msg(client_id[input_id],msg);
                        }
                    }

                }

                // Killing child
                _exit(EXIT_SUCCESS);
            }

        } else {

//             Increase id counter
            if (type == 1)
                id++;

        }
    }


}










