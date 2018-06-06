/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <zconf.h>

#include "utils.c"
#include "../server.h"

int main(int argc, char *argv[])
{
    int sockfd, portno, clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;


    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }

    if( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
        error_and_die("socket: error while opening socket\n");

    bzero((char *) &serv_addr, sizeof(serv_addr));

    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error_and_die("bind: ERROR on binding\n");

    listen(sockfd,5);

    while(1){
        clilen = sizeof(cli_addr);
        if( (cl_sock[cl_counter] = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen)) < 0)
            error_and_die("accept: ERROR on accept\n");

        bzero(buffer, sizeof(buffer));
        read(cl_sock[cl_counter] ,buffer,255);
        printf("Here is the message: %s\n",buffer);

        cl_counter++;
        if(cl_counter == 2)
            break;
    }

    return 0;
}