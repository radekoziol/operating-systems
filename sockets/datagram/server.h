//
// Created by radekkoziol on 06.06.18.
//

#ifndef SOCKETS_SERVER_H
#define SOCKETS_SERVER_H

#define MAX_CLIENT_NUM 128

int cl_sock[MAX_CLIENT_NUM];
int cl_counter = 0;


struct message{
    // 0 -> register, 1-> operation
    int type;
    char sender_name[32];
    // ADD, SUB, MUL, DIV
    char operation[3];
    int arg1,arg2;
};


#endif //SOCKETS_SERVER_H
