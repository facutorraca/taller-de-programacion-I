#include "sudoku_server.h"
#include "sudoku.h"
#include "message.h"
#include "server.h"
#include <stdio.h>
#include <stdbool.h>

#define SUCCESS 0
#define ERROR 1

int control_recv(message_t* msg) {
    if(message_get_length(msg) == 0) {
        return ERROR;
    }
    char frt = message_get_first_character(msg);
    if(frt == 'G' || frt == 'V' || frt == 'R') {
        return SUCCESS;
    }
    if(frt == 'P' && message_get_length(msg) == 4){
        return SUCCESS;
    }
    return ERROR;
}

int sudoku_server_process_message(message_t* msg, sudoku_t* sudoku) {
    printf("%s\n",msg->buffer);
    //for(int i = 0; i < msg->len_msg; i++){
    //    printf("%c",msg->buffer[i]);
    //}
    return SUCCESS;
}

int sudoku_server_wait_instructions(sudoku_server_t* sudoku_server) {
    message_t msg;
    while (true) {
        message_init(&msg); //Init a message with length 0
        server_start_to_receive(&sudoku_server->server, &msg, control_recv);
        sudoku_server_process_message(&msg, &sudoku_server->sudoku);
    }
    return SUCCESS;
}

int sudoku_server_start(const char* port) {
    server_t server;
    server_init(&server, port);

    sudoku_t sudoku;
    sudoku_init(&sudoku);

    sudoku_server_t sudoku_server;
    sudoku_server.server = server;
    sudoku_server.sudoku = sudoku;

    server_start_to_listen(&sudoku_server.server);
    printf("Coneccion establecida\n");

    sudoku_server_wait_instructions(&sudoku_server);
    return SUCCESS;
}
