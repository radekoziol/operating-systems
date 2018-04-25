//
// Created by radekkoziol on 20.04.18.
//

#include <sys/stat.h>
#include <fcntl.h>
#include <zconf.h>
#include <stdio.h>
#include <sys/msg.h>
#include <memory.h>
#include <stdlib.h>
#include <errno.h>
#include "utils.c"

#define MSGTXTLEN 128   // msg text length
#define MSGPERM 0600    // msg queue permission
#define MAX_BUF 1024



int main() {

    char buf[MAX_BUF];
    // Open file in write mode
    FILE *fp = fopen("../server_id.txt","r");

    // If file opened successfully, then write the string to file
    if ( fp )
    {
        char writestr[100];
        fread(writestr,100, sizeof(char),fp);
    }
    else
    {
        printf("Failed to open the file\n");
    }
    //Close the file
    fclose(fp);

    int server_id = (int) strtol(buf, NULL, 10);

    // Creating private queue
    int client_id = msgget(IPC_PRIVATE, MSGPERM | IPC_CREAT | IPC_EXCL);

    if (client_id < 0) {
        perror(strerror(errno));
        printf("failed to create message queue with msgqid = %d\n", client_id);
        return 1;
    }

    struct msgbuf msg1;
    struct msgbuf msg2;

    msg1.mtype = 1;
    sprintf(msg1.mtext, "%d", client_id);

    printf("Sending request for private channel: %s\n", msg1.mtext);

    int rc = msgsnd(server_id, &msg1, sizeof(msg1.mtext), 0);

    if (rc < 0) {
        perror(strerror(errno));
        printf("msgsnd failed, rc = %d\n", rc);
        return 1;
    }


    if (msgrcv(client_id, &msg2, 1024, 0, 0)) {
        printf("Received from server %s\n", msg2.mtext);
    }
    int id = (int) strtol(msg2.mtext,NULL,10);

    struct msgbuf msg3;
    struct msgbuf msg4;




    for(int i = 1; i < 5; i++){

        msg3 = generate_random_calculation_request(id);
        printf("Sending operation request: %s\n", msg3.mtext);

        rc = msgsnd(server_id, &msg3, sizeof(msg3.mtext), 0);
        if (rc < 0) {
            perror(strerror(errno));
            printf("msgsnd failed, rc = %d\n", rc);
            return 1;
        }


        msg4.mtype = 0;
        if (msgrcv(client_id, &msg4, 1024, 0, 0)) {

            printf("Received calculations from server %s\n", msg4.mtext);
        }

    }


    msgctl(client_id, IPC_RMID, NULL);
}
