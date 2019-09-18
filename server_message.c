#include "server_message.h"
#include "answer_server.h"
#include "message.h"
#include "server.h"
#include "sudoku.h"
#include "utils.h"
#include <arpa/inet.h>
#include <stdio.h>

#define BYTES_LEN 4

static int calculate_length_message(server_message_t* self) {
    uint32_t length = htonl(message_get_length(&self->message));

    char array_with_length[BYTES_LEN];
    uint_to_array(array_with_length, length);

    message_create(&self->len_msg, array_with_length, BYTES_LEN);
    return SUCCESS;
}

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

int reset_messages(server_message_t* self) {
    message_init(&self->message);
    message_init(&self->len_msg);
    return SUCCESS;
}

int server_message_recv(server_message_t* self) {
    if (!self->server) {
        return ERROR;
    }
    reset_messages(self);
    return server_recv(self->server, &self->message, control_recv_server);
}

int server_message_send(server_message_t* self) {
    if (!self->server) {
        return ERROR;
    }
    calculate_length_message(self);
    server_send(self->server, &self->len_msg);
    server_send(self->server, &self->message);
    return SUCCESS;
}

int server_message_create_answer(server_message_t* self, sudoku_t* sudoku) {
    answer_server_create(&self->message, sudoku);
    //calculate_length_message
    return SUCCESS;
}

int server_message_set_server(server_message_t* self, server_t* server) {
    self->server = server;
    return SUCCESS;
}

int server_message_init(server_message_t* self) {
    message_init(&self->message);
    message_init(&self->len_msg);
    self->server = NULL;
    return SUCCESS;
}

int server_message_release(server_message_t* self) {
    message_release(&self->message);
    message_release(&self->len_msg);
    self->server = NULL;
    return SUCCESS;
}
