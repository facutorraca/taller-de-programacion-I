#include "sudoku_client.h"
#include "interface.h"
#include "verifier.h"
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

int control_recv_client(message_t* msg) {
    if (message_get_length(msg) < 4) {
        return ERROR;
    }
    uint32_t len = ntohl((msg->buffer[0] <<  24) | (msg->buffer[1] << 16) | (msg->buffer[2] << 8) | msg->buffer[3]);
    if (message_get_length(msg) < len + 4) {
        return ERROR;
    }
    return SUCCESS;
}

int show_msg(message_t* msg) {
    for (int i = 0; i < 19; i++) {
        for (int j = 0; j < 37; j++) {
            printf("%c",msg->buffer[(i*36+j)+4]);
        }
        printf("\n");
    }
    return SUCCESS;
}

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

uint32_t sudoku_client_decode_msg(client_t* client, message_t* msg) {
    char buffer[4];
    message_copy_in_buffer(msg, buffer, 4);
    return ntohl((buffer[0] <<  24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3]);
}

int sudoku_client_start_to_recv(client_t* client, message_t* msg) {
//    message_t msg;
//    message_init(&msg);
    client_start_to_recv(client, msg, control_recv_client);
    show_msg(msg);
    return SUCCESS;
    /*
    uint32_t len  = sudoku_client_get_length_next_message(client, msg);
    client_start_to_recv(client, msg, len);
    */
}

int sudoku_client_start_to_send(client_t* client, message_t* msg) {
    char buffer_ins[MAX_BUFFER_INS];
    interface_get_new_instruction(buffer_ins, MAX_BUFFER_INS);
    sudoku_client_process_instruction(msg, buffer_ins);
    client_start_to_send(client, msg);
    return SUCCESS;
}

int sudoku_client_start_connection(client_t* client) {
    message_t msg;
    while (true) {
        message_init(&msg); //Initialize new message
        sudoku_client_start_to_send(client, &msg);
        message_init(&msg); //Initialize new message
        sudoku_client_start_to_recv(client, &msg);
    }
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
