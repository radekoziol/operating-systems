//
// Created by radekkoziol on 20.04.18.
//

#include <sys/stat.h>
#include <fcntl.h>
#include <zconf.h>
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include "utils.c"
#include "posix.h"

char queue_name[128] = "/client_queue";

void read_server_name(char *server_name) {

    // Open file in write mode
    FILE *fp = fopen("../server_id.txt", "r");
    for (int i = 0; i < MSG_SIZE; i++) server_name[i] = '\0';

    // If file opened successfully, then write the string to file
    if (fp) {
        fread(server_name, MSG_SIZE, sizeof(char), fp);
    } else {
        printf("Failed to open the file\n");
    }
    //Close the file
    fclose(fp);
}

int server_up() {

    mqd_t mqd;

    // Creating private queue
    struct mq_attr attr;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = MSG_SIZE;
    attr.mq_curmsgs = 0;


    if ((mqd = mq_open(queue_name, O_CREAT | O_RDONLY, 0644, &attr)) == -1) {
        perror("mq_open() error");
        exit(-1);
    }

    printf("Queue successfully created with following attributes: \n");
    mq_getattr(mqd, &attr);
    printf("max #msgs = %ld,max #bytes/msg = %ld,#currently on queue = %ld\n",
           attr.mq_maxmsg, attr.mq_msgsize, attr.mq_curmsgs);
    return mqd;
}


mqd_t open_server(const char *server_name) {
    mqd_t s_mqd;

    if ((s_mqd = mq_open(server_name, O_WRONLY)) == -1) {
        perror("mq_open() error");
        exit(-1);
    }
    printf("Server queue successfully opened!\n");

    return s_mqd;
}


int main() {

    char server_name[MSG_SIZE];

    read_server_name(server_name);

    mqd_t s_mqd = open_server(server_name);

    mqd_t mqd = server_up();

    char msg[1024];
    sprintf(msg, "%s:%s", "1", queue_name);

    if (mq_send(s_mqd, msg, strlen(msg), 1) >= 0) {
        printf("Mssg send successfully\n");
    } else {
        perror("mq_open() error");
        exit(-1);
    }

    char msg1[MSG_SIZE];
    if (mq_receive(mqd, msg1, sizeof(msg1), NULL) >= 0) {
        printf("Received id from server: %s\n", msg1);
    }

    long id = strtol(msg1, NULL, 10);

    for (int i = 1; i < 5; i++) {

        char *op_req = calloc(128, sizeof(char));
        op_req = generate_random_calculation_request(id);
        char op_request[1024];
        sprintf(op_request, "%s", op_req);

        printf("Sending operation request: %s\n", op_request);

        if (mq_send(s_mqd, op_request, strlen(op_request), 1) >= 0) {
        } else {
            perror("mq_open() error");
            exit(-1);
        }


        char result[MSG_SIZE];
        memset(result, 0, sizeof result);
        if (mq_receive(mqd, result, sizeof(result), NULL) >= 0) {
            printf("Received results from server: %s\n", result);
        }

    }

    mq_close(mqd);

}
