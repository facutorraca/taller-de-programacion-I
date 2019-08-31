#include "sudoku_client.h"
#include "interface.h"
#include "verifier.h"
#include "client.h"
#include "message.h"
#include <stdbool.h>
#include <stdio.h>

#define MAX_BUFFER_INS 20 //Buffer to save instruction
#define SUCCESS 0
#define ERROR 1


int sudoku_client_process_instruction(message_t* msg, const char* buffer_ins) {
    if(buffer_ins[0] == 'p' && verifier_verify_put_instruction(buffer_ins)) {
        message_append_character(msg, 'P');
        message_append_character(msg, buffer_ins[4]);
        message_append_character(msg, buffer_ins[9]);
        message_append_character(msg, buffer_ins[11]);
        return SUCCESS;
    } else if(buffer_ins[0] == 'g' && verifier_verify_get_instruction(buffer_ins)) {
            message_append_character(msg, 'G');
            return SUCCESS;
    } else if(buffer_ins[0] == 'v' && verifier_verify_verify_instruction(buffer_ins)) {
            message_append_character(msg, 'V');
            return SUCCESS;
    } else if(buffer_ins[0] == 'r' && verifier_verify_reset_instruction(buffer_ins)) {
            message_append_character(msg, 'R');
            return SUCCESS;
    }
    return ERROR;
}

int sudoku_client_wait_instructions(client_t* client) {
    message_t msg;
    char buffer_ins[MAX_BUFFER_INS];
    while (true) {
        message_init(&msg); //Initialize new message
        interface_get_new_instruction(buffer_ins, MAX_BUFFER_INS);
        sudoku_client_process_instruction(&msg, buffer_ins);
        client_start_to_send(client, msg);
    }
}

int sudoku_client_start(const char* host, const char* port) {
    client_t client;
    client_init(&client, host, port);
    client_connect_with_server(&client);
    //waint instructions to the server
    sudoku_client_wait_instructions(&client);
    return SUCCESS;
}
