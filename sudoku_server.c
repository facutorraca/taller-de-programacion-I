#include "sudoku_server.h"
#include "sudoku.h"
#include "utils.h"
#include "message.h"
#include "interface.h"
#include "server.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <arpa/inet.h>

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

int sudoku_server_get_board_to_send(sudoku_t* sudoku, message_t* msg) {
    char board_numbers[81];
    char board_design[703];
    sudoku_get_board_numbers(sudoku, board_numbers);
    interface_get_board_design(board_design, board_numbers);
    message_create(msg, board_design, 703);
    return SUCCESS;
}

int sudoku_server_put_instruction(sudoku_t* sudoku, message_t* msg) {
    char* msg_buf = message_get(msg);
    sudoku_put_number(sudoku, msg_buf[1], msg_buf[2], msg_buf[3]);
    message_init(msg); //Restart the message
    sudoku_server_get_board_to_send(sudoku, msg);
    return SUCCESS;
}

int sudoku_server_rst_instruction(sudoku_t* sudoku, message_t* msg) {
    message_init(msg); //Restart the message
    sudoku_reset(sudoku);
    sudoku_server_get_board_to_send(sudoku, msg);
    return SUCCESS;
}

int sudoku_server_vrf_instruction(sudoku_t* sudoku, message_t* msg) {
    message_init(msg);
    if(sudoku_verify(sudoku) == SUCCESS) {
        message_create(msg, "OK\n", 3);
    } else {
        message_create(msg, "ERROR\n", 6);
    }
    return SUCCESS;
}

int sudoku_server_get_instruction(sudoku_t* sudoku, message_t* msg) {
    message_init(msg); //Restart the message
    sudoku_server_get_board_to_send(sudoku, msg);
    return SUCCESS;
}

int sudoku_server_process_send_message(message_t* msg, server_t* server) {
    uint32_t len = htonl(message_get_length(msg));

    char array_with_len[4];
    uint_to_array(array_with_len, len);

    message_t msg_with_len;
    message_create(&msg_with_len, array_with_len, 4);
    message_concat(&msg_with_len, msg);

    //The message now is a message with len
    *msg = msg_with_len;
    return SUCCESS;
}

int sudoku_server_process_recv_message(message_t* msg, sudoku_t* sudoku) {
    if (message_get_first_character(msg) == 'G') {
        sudoku_server_get_instruction(sudoku, msg);
    }
    if (message_get_first_character(msg) == 'V') {
        sudoku_server_vrf_instruction(sudoku, msg);
    }
    if (message_get_first_character(msg) == 'R') {
        sudoku_server_rst_instruction(sudoku, msg);
    }
    if (message_get_first_character(msg) == 'P') {
        sudoku_server_put_instruction(sudoku, msg);
    }
    return SUCCESS;
}

int sudoku_server_start_to_send(sudoku_server_t* sudoku_server, message_t* msg) {
    sudoku_server_process_send_message(msg, &sudoku_server->server);
    server_start_to_send(&sudoku_server->server, msg);
    return SUCCESS;
}

int sudoku_server_start_to_recv(sudoku_server_t* sudoku_server, message_t* msg) {
    server_start_to_recv(&sudoku_server->server, msg, control_recv_server);
    sudoku_server_process_recv_message(msg, &sudoku_server->sudoku);
    return SUCCESS;
}

int sudoku_server_start_connection(sudoku_server_t* sudoku_server) {
    message_t msg; //Message to communicate with client
    while (true) {
        message_init(&msg);
        sudoku_server_start_to_recv(sudoku_server, &msg);
        sudoku_server_start_to_send(sudoku_server, &msg);
    }
    return SUCCESS;
}

int sudoku_server_init(sudoku_server_t* sudoku_server, const char* port) {
    server_t server;
    server_init(&server, port);

    sudoku_t sudoku;
    sudoku_init(&sudoku);

    sudoku_server->server = server;
    sudoku_server->sudoku = sudoku;
    return SUCCESS;
}

int sudoku_server_start(const char* port) {
    sudoku_server_t sudoku_server;
    sudoku_server_init(&sudoku_server, port);

    server_start_to_listen(&sudoku_server.server);
    interface_conection_success();

    sudoku_server_start_connection(&sudoku_server);
    return SUCCESS;
}
