#include "sudoku_server.h"
#include "sudoku.h"
#include "message.h"
#include "interface.h"
#include "server.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <arpa/inet.h>

#define SUCCESS 0
#define ERROR 1

int control_recv_server(message_t* msg) {
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

int sudoku_server_get_board_to_send(sudoku_t* sudoku, message_t* board_msg) {
    char board_numbers[81];
    char board_design[703];
    sudoku_get_board_numbers(sudoku, board_numbers);
    interface_get_board_design(board_design, board_numbers);
    message_create(board_msg, board_design, 703);
    return SUCCESS;
}

int sudoku_server_put_instruction(sudoku_t* sudoku, char num, char row, char col, message_t* msg) {
    sudoku_put_number(sudoku, num, row, col);
    sudoku_server_get_board_to_send(sudoku, msg);
    return SUCCESS;
}

int sudoku_server_rst_instruction(sudoku_t* sudoku, message_t* msg) {
    sudoku_reset(sudoku);
    sudoku_server_get_board_to_send(sudoku, msg);
    return SUCCESS;
}

int sudoku_server_vrf_instruction(sudoku_t* sudoku, message_t* msg) {
    if(sudoku_verify(sudoku) == SUCCESS) {
        message_create(msg, "OK\n", 3);
    } else {
        message_create(msg, "ERROR\n", 6);
    }
    return SUCCESS;
}

int sudoku_server_process_recv_message(message_t* msg, sudoku_t* sudoku) {
    char inst[4];
    message_copy_in_buffer(msg, inst, 4);
    message_init(msg); //Restart the message with length 0
    if (inst[0] == 'G') {
        sudoku_server_get_board_to_send(sudoku, msg);
    }
    if (inst[0] == 'V') {
        sudoku_server_vrf_instruction(sudoku, msg);
    }
    if (inst[0] == 'R') {
        sudoku_server_rst_instruction(sudoku, msg);
    }
    if (inst[0] == 'P') {
        sudoku_server_put_instruction(sudoku, inst[1], inst[2], inst[3], msg);
    }
    return SUCCESS;
}

int sudoku_server_process_send_message(message_t* msg, server_t* server) {
    uint32_t len = htonl(message_get_length(msg));

    //Save the uint32 var in a char vector
    char buf_len[4];
    buf_len[0] = len >> 24;
    buf_len[1] = len >> 16;
    buf_len[2] = len >> 8;
    buf_len[3] = len;

    message_t msg_with_len;
    message_create(&msg_with_len, buf_len, 4);
    message_concat(&msg_with_len, msg);

    //The message now is a message with len
    *msg = msg_with_len;
    return SUCCESS;
}

int sudoku_server_start_to_recv(sudoku_server_t* sudoku_server, message_t* msg) {
    server_start_to_receive(&sudoku_server->server, msg, control_recv_server);
    sudoku_server_process_recv_message(msg, &sudoku_server->sudoku);
    return SUCCESS;
}

int sudoku_server_start_to_send(sudoku_server_t* sudoku_server, message_t* msg) {
    sudoku_server_process_send_message(msg, &sudoku_server->server);
    server_start_to_send(&sudoku_server->server, msg);
    return SUCCESS;
}

int sudoku_server_start_connection(sudoku_server_t* sudoku_server) {
    message_t msg;
    while (true) {
        message_init(&msg); //Init a message with length 0
        sudoku_server_start_to_recv(sudoku_server, &msg);
        sudoku_server_start_to_send(sudoku_server, &msg);
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
    printf("Coneccion establecida...\n");

    sudoku_server_start_connection(&sudoku_server);
    return SUCCESS;
}
