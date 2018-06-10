#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <zconf.h>
#include <memory.h>
#include <arpa/inet.h>
#include "utils.c"

void error(char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {
    int sockfd, portno, n;

    struct sockaddr_in serv_addr;

//    char buffer[256];
//    if (argc < 3) {
//        fprintf(stderr, "usage %s hostname port\n", argv[0]);
//        exit(0);
//    }

    portno = 51717;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket");


    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portno);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting");

    char buffer[256];



    // Registering
    bzero(buffer, 256);
    send(sockfd, "Radek", 9, 0);

    //     Reading calculations res
    bzero(buffer, 256);
    recv(sockfd, buffer, sizeof(buffer), 0);
    while(strlen(buffer) <= 1 ){
        recv(sockfd, buffer, sizeof(buffer), 0);
    }
//    while (1){
//        if(strcmp("0",buffer) != 0)
//            break;
//        else{
//            bzero(buffer, 256);
//            read(sockfd, buffer, sizeof(buffer));
//        }
//    }

    printf("Received %s\n", buffer);

    calculate_arth_expr(buffer);
    char response[128];
    memset(response, '\0', 128);

    sprintf(response, "%s:%s", "RadekK", buffer);

    n = (int) send(sockfd, response, strlen(response), 0);
    if (n < 0)
        error("ERROR writing to socket");


    close(sockfd);


    return 0;
}