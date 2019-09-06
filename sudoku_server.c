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

#define SIZE_BOARD 722
#define NUM_NUMBERS 81

int control_recv_server(message_t* msg) {
    if (message_get_length(msg) == 0) {
        //server read 0 bytes so socket is closed
        return SUCCESS;
    }
    char frt = message_get_first_character(msg);
    if (frt == 'G' || frt == 'V' || frt == 'R') {
        return SUCCESS;
    }
    if (frt == 'P' && message_get_length(msg) == 4){
        return SUCCESS;
    }
    return ERROR;
}

int prepare_message_with_board(sudoku_t* sudoku, message_t* msg) {
    char board_numbers[NUM_NUMBERS];
    char board_drawing[SIZE_BOARD];
    memset(board_numbers, 0, NUM_NUMBERS * sizeof(char));
    memset(board_drawing, 0, SIZE_BOARD * sizeof(char));

    sudoku_get_board_numbers(sudoku, board_numbers);
    interface_get_board_design(board_drawing, board_numbers);
    message_create(msg, board_drawing, SIZE_BOARD);
    return SUCCESS;
}

int process_put_instruction(sudoku_t* sudoku, message_t* msg) {
    char* msg_buf = message_get(msg);
    if (sudoku_put_number(sudoku, msg_buf[3], msg_buf[1], msg_buf[2]) == SUCCESS) {
        message_init(msg); //Restart the message
        prepare_message_with_board(sudoku, msg);
    } else {
        message_init(msg); //Restart the message
        message_create(msg, "La celda indicada no es modificable\n", 36);
    }
    return SUCCESS;
}

int process_rst_instruction(sudoku_t* sudoku, message_t* msg) {
    message_init(msg); //Restart the message
    sudoku_reset(sudoku);
    prepare_message_with_board(sudoku, msg);
    return SUCCESS;
}

int process_vrf_instruction(sudoku_t* sudoku, message_t* msg) {
    message_init(msg); //Restart the message
    if (sudoku_verify(sudoku) == SUCCESS) {
        message_create(msg, "OK\n", 3);
    } else {
        message_create(msg, "ERROR\n", 6);
    }
    return SUCCESS;
}

int process_get_instruction(sudoku_t* sudoku, message_t* msg) {
    message_init(msg); //Restart the message
    prepare_message_with_board(sudoku, msg);
    return SUCCESS;
}

static int process_length_message(message_t* msg, message_t* length_msg) {
    uint32_t length = htonl(message_get_length(msg));

    char array_with_length[4];
    uint_to_array(array_with_length, length);

    message_create(length_msg, array_with_length, 4);
    return SUCCESS;
}

static int process_recv_message(message_t* msg, sudoku_t* sudoku) {
    if (message_get_first_character(msg) == 'G') {
        process_get_instruction(sudoku, msg);
    }
    if (message_get_first_character(msg) == 'V') {
        process_vrf_instruction(sudoku, msg);
    }
    if (message_get_first_character(msg) == 'R') {
        process_rst_instruction(sudoku, msg);
    }
    if (message_get_first_character(msg) == 'P') {
        process_put_instruction(sudoku, msg);
    }
    return SUCCESS;
}

static int start_to_send(sudoku_server_t* sudoku_server, message_t* msg) {
    message_t length_msg; //Msg with length of next message
    process_length_message(msg, &length_msg);
    server_start_to_send(&sudoku_server->server, &length_msg);
    server_start_to_send(&sudoku_server->server, msg);
    return SUCCESS;
}

static int start_to_recv(sudoku_server_t* sudoku_server, message_t* msg) {
    if (server_start_to_recv(&sudoku_server->server, msg, control_recv_server) == 0) {
        return ERROR;
    }
    process_recv_message(msg, &sudoku_server->sudoku);
    return SUCCESS;
}

int sudoku_server_start_connection(sudoku_server_t* sudoku_server) {
    message_t msg; //Message to communicate with client

    bool connected = true;
    while (connected) {
        message_init(&msg);
        if (start_to_recv(sudoku_server, &msg) == ERROR){
            connected = false;
        }
        if (connected) {
            start_to_send(sudoku_server, &msg);
        }
    }
    server_release(&sudoku_server->server);
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
    sudoku_server_start_connection(&sudoku_server);
    return SUCCESS;
}
