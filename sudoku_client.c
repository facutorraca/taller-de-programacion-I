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

//DE PRUEBA!
int show_msg(message_t* msg) {
    if(msg->len_msg == 703) {
        for (int i = 0; i < 19; i++) {
            for (int j = 0; j < 37; j++) {
                printf("%c",msg->buffer[(i*36+j)]);
            }
            printf("\n");
        }
    }
    else {
        for (int j = 0; j < msg->len_msg; j++) {
            printf("%c",msg->buffer[j]);
        }
    }
    return SUCCESS;
}

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
    show_msg(msg);
    return SUCCESS;
}

int sudoku_client_start_to_send(client_t* client, message_t* msg) {
    char buffer_ins[MAX_BUFFER_INS];
    interface_get_new_instruction(buffer_ins, MAX_BUFFER_INS);
    sudoku_client_process_send_message(msg, buffer_ins);
    client_start_to_send(client, msg);
    return SUCCESS;
}

int sudoku_client_start_connection(client_t* client) {
    message_t msg; //Message to communicate with server
    while (true) {
        message_init(&msg); //Initialize new message
        sudoku_client_start_to_send(client, &msg);
        message_init(&msg); //Restart the message
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
