#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <strings.h>
#include <zconf.h>
#include <memory.h>
#include <arpa/inet.h>
#include <time.h>
#include "utils.c"

void error(char *msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[]) {


    // Example input
    argc = 3;
    argv[1] = "Radek123";
    argv[2] = "127.0.0.1";
    argv[3] = "51717";


    int sockfd, portno, n;
    struct sockaddr_in serv_addr;

    if (argc < 3) {
        printf("Arguments are: <type> <address> opt <port>\n");
        exit(1);
    }

    portno = strtol(argv[3],NULL,10);

    if(argc == 2){
        sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
        if (sockfd < 0)
            error("ERROR opening socket");

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int) {1}, sizeof(int)) < 0)
            error("setsockopt(SO_REUSEADDR) failed");

        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_UNIX;
        serv_addr.sin_port = htons((uint16_t) portno);
        inet_pton(AF_UNIX, argv[2], &serv_addr.sin_addr);

        if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
            error("ERROR connecting");

    }else{
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
            error("ERROR opening socket");

        if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int) {1}, sizeof(int)) < 0)
            error("setsockopt(SO_REUSEADDR) failed");

        bzero((char *) &serv_addr, sizeof(serv_addr));
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons((uint16_t) portno);
        inet_pton(AF_INET, argv[2], &serv_addr.sin_addr);

        if (connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
            error("ERROR connecting");

    }



    char buffer[256];

    // Registering
    bzero(buffer, 256);
    char name[128];
    memset(name, '\0', 128);

    srand((unsigned int) time(NULL));

    sprintf(name, "%s", argv[1]);

    send(sockfd, name, strlen(name), 0);

    //     Reading calculations res
    bzero(buffer, 256);
    recv(sockfd, buffer, sizeof(buffer), 0);
    while (strlen(buffer) <= 1) {
        recv(sockfd, buffer, sizeof(buffer), 0);
    }

    printf("Received %s\n", buffer);

    calculate_arth_expr(buffer);

    n = (int) send(sockfd, buffer, strlen(buffer), 0);
    if (n < 0)
        error("ERROR writing to socket");

    close(sockfd);


    return 0;
}