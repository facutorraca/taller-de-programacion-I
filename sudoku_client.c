#include "sudoku_client.h"
#include "interface.h"
#include "verifier.h"
#include "utils.h"
#include "client.h"
#include "message.h"
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <stdint.h>

#define MAX_BUFFER_INS 20 //Buffer to save instruction
#define SUCCESS 0
#define ERROR 1

int sudoku_client_put_instruction(message_t* msg, const char* instruction) {
    message_append_character(msg, 'P');
    message_append_character(msg, instruction[4]);
    message_append_character(msg, instruction[9]);
    message_append_character(msg, instruction[11]);
    return SUCCESS;
}

int sudoku_client_process_send_message(message_t* msg, const char* instruction) {
    if (strcmp(instruction, "get\n") == 0) {
        return message_append_character(msg, 'G');
    } else if (strcmp(instruction, "verify\n") == 0) {
        return message_append_character(msg, 'V');
    } else if (strcmp(instruction, "reset\n") == 0) {
        return message_append_character(msg, 'R');
    } else {   /* put instruction case */
        return sudoku_client_put_instruction(msg, instruction);
    }
}

uint32_t process_length_message(message_t* msg) {
    char array_with_len[4];
    message_get_nfirst(msg, array_with_len, 4);
    return ntohl(array_to_uint(array_with_len));
    return SUCCESS;
}

int sudoku_client_start_to_recv(client_t* client, message_t* msg) {
    client_start_to_recv(client, msg, 4);
    uint32_t len_next_message = process_length_message(msg);

    message_init(msg); //Restart the message to receive the new one
    client_start_to_recv(client, msg, len_next_message);
    return SUCCESS;
}

int sudoku_client_start_to_send(client_t* client, message_t* msg) {
    client_start_to_send(client, msg);
    return SUCCESS;
}

int sudoku_client_close(client_t* client) {
    client_release(client);
    return SUCCESS;
}

int sudoku_client_start_connection(client_t* client) {
    char inst[MAX_BUFFER_INS] = {0};
    int get_inst_flag = interface_get_new_instruction(inst, MAX_BUFFER_INS);

    message_t msg;
    while (strcmp("exit\n",inst) != 0 && get_inst_flag == SUCCESS) {
        message_init(&msg); //Initialize new message
        sudoku_client_process_send_message(&msg, inst);
        sudoku_client_start_to_send(client, &msg);

        message_init(&msg); //Restart the message
        sudoku_client_start_to_recv(client, &msg);
        interface_print_message(&msg);
        get_inst_flag = interface_get_new_instruction(inst, MAX_BUFFER_INS);
    }

    sudoku_client_close(client);
    return SUCCESS;
}

int sudoku_client_start(const char* host, const char* port) {
    client_t client;
    client_init(&client, host, port);
    client_connect_with_server(&client);
    //waint instructions to the server
    sudoku_client_start_connection(&client);
    return SUCCESS;
}
