#include "sudoku_client.h"
#include "interface.h"
#include "utils.h"
#include "message.h"
#include "client.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <arpa/inet.h>

#define MAX_INST 20

int sudoku_client_close(client_t* client) {
    client_release(client);
    return SUCCESS;
}

int prepare_put_instruction(message_t* msg, char row, char col, char num) {
    message_append_character(msg, 'P');
    message_append_character(msg, row);
    message_append_character(msg, col);
    message_append_character(msg, num);
    return SUCCESS;
}

static int process_send_message(message_t* msg, const char* inst) {
    if (strcmp(inst, "get\n") == 0) {
        return message_append_character(msg, 'G');
    } else if (strcmp(inst, "verify\n") == 0) {
        return message_append_character(msg, 'V');
    } else if (strcmp(inst, "reset\n") == 0) {
        return message_append_character(msg, 'R');
    } else {   /* put instruction case */
        return prepare_put_instruction(msg, inst[9], inst[11], inst[4]);
    }
}

static uint32_t process_length_message(message_t* msg) {
    char array_with_length[4];
    memset(inst, 0, 4 * sizeof(char));

    message_get_nfirst(msg, array_with_length, 4);
    return ntohl(array_to_uint(array_with_len));
}

static int start_to_recv(client_t* client, message_t* msg) {
    client_start_to_recv(client, msg, 4);
    uint32_t length_next_message = process_length_message(msg);

    message_init(msg); //Restart the message to receive the new one
    client_start_to_recv(client, msg, length_next_message);
    return SUCCESS;
}

static int start_to_send(client_t* client, message_t* msg, char* inst) {
    process_send_message(msg, inst);
    client_start_to_send(client, msg);
    return SUCCESS;
}

int get_new_instuction(char* inst) {
    memset(inst, 0, MAX_INST * sizeof(char)); //restart the buffer
    return interface_get_new_instruction(inst, MAX_INST);
}

bool is_exit_instruction(char* inst) {
    return strcmp(inst, "exit\n") == 0;
}

int sudoku_client_start_connection(client_t* client) {
    char inst[MAX_INST];

    message_t msg;
    while (get_new_instuction(inst) != ERROR && !is_exit_instruction(inst)) {
        message_init(&msg); //Initialize new message
        sudoku_client_start_to_send(client, &msg, inst);

        message_init(&msg); //Restart the message
        sudoku_client_start_to_recv(client, &msg);
        interface_print_message(&msg);
    }

    sudoku_client_close(client);
    return SUCCESS;
}

int sudoku_client_start(const char* host, const char* port) {
    client_t client;
    client_init(&client, host, port);
    client_connect_with_server(&client);

    sudoku_client_start_connection(&client);
    return SUCCESS;
}
