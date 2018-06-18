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
#include <sys/socket.h>
#include <sys/un.h>

int sockfd;
struct sockaddr_in serv_addr_dgram;


void error(char *msg) {
    perror(msg);
    exit(0);
}

void run_dgram_sock(int portno, char *host_addr) {



    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        error_and_die("socket: error while opening socket\n");

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int) {1}, sizeof(int)) < 0)
        error_and_die("setsockopt(SO_REUSEADDR) failed");

    make_unblocking(sockfd);


    bzero((char *) &serv_addr_dgram, sizeof(serv_addr_dgram));

    serv_addr_dgram.sin_family = AF_INET;
    serv_addr_dgram.sin_addr.s_addr = inet_addr(host_addr);
    serv_addr_dgram.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &serv_addr_dgram, sizeof(serv_addr_dgram)) < 0)
        error_and_die("bind: ERROR on binding\n");

}

void run_unix_sock(char *addr) {

    if ((sockfd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
        error_and_die("socket: error while opening socket\n");

    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int) {1}, sizeof(int)) < 0)
        error_and_die("setsockopt(SO_REUSEADDR) failed");

    make_unblocking(sockfd);

    struct sockaddr_un serv_addr_unix = {AF_UNIX, addr};

    if (bind(sockfd, (struct sockaddr *) &serv_addr_unix, sizeof(serv_addr_unix)) < 0)
        error_and_die("bind: ERROR on binding\n");


}

int main(int argc, char *argv[]) {


//    argc = 3;
//    argv[1] = "client_1";
//    argv[2] = "192.168.0.31";
//    argv[3] = "51717";

    if (argc < 3) {
        printf("Arguments are: <type> <address> opt <port>\n");
        exit(1);
    }

    char *host_addr, *unix_addr;


    int portnum;
    if (argc == 2) {
        unix_addr = argv[2];
        run_unix_sock(unix_addr);

        struct sockaddr_un serv_addr_unix = {AF_UNIX, unix_addr};

        if (connect(sockfd, (struct sockaddr *) &serv_addr_unix, sizeof(serv_addr_unix)) < 0)
            error("ERROR connecting");


    } else {
        host_addr = argv[2];
        portnum = (int) strtol(argv[3], NULL, 10);
        run_dgram_sock(portnum, host_addr);

        if (connect(sockfd, (struct sockaddr *) &serv_addr_dgram, sizeof(serv_addr_dgram)) < 0)
            error("ERROR connecting");
    }


    // Registering

    struct sockaddr_in si_other;
    memset((char *) &si_other, 0, sizeof(si_other));
    si_other.sin_family = AF_INET;
    si_other.sin_port = htons(portnum);
    if (inet_aton(argv[2] , &si_other.sin_addr) == 0)
    {
        fprintf(stderr, "inet_aton() failed\n");
        exit(1);
    }

    char buffer[256];
    size_t slen=sizeof(si_other);
    sendto(sockfd, buffer, strlen(buffer) , 0 , (struct sockaddr *) &si_other, slen );

    //     Reading calculations res

    bzero(buffer, 256);
    recv(sockfd, buffer, sizeof(buffer), 0);
    while (strlen(buffer) <= 1) {
        recv(sockfd, buffer, sizeof(buffer), 0);
    }

    printf("Received %s\n", buffer);

    calculate_arth_expr(buffer);

    sendto(sockfd, buffer, strlen(buffer) , 0 , (struct sockaddr *) &si_other, slen );

    close(sockfd);


    return 0;
}