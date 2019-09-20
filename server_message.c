#include "server_message.h"
#include "answer_server.h"
#include "server.h"
#include "sudoku.h"
#include "utils.h"
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>

#define BYTES_LEN 4

int control_recv_server(char* msg) {
    if (msg[0] == 'G' || msg[0] == 'V' || msg[0] == 'R') {
        return SUCCESS;
    } else {
        return ERROR;
    }
}

int reset_messages(server_message_t* self) {
    memset(self->message, 0, MAX_LEN_MSG * sizeof(char));
    self->len_msg = 0;
    return SUCCESS;
}

int server_message_recv(server_message_t* self) {
    if (!self->server) {
        return ERROR;
    }
    reset_messages(self);
    return server_recv(self->server, self->message, control_recv_server);
}

int server_message_send(server_message_t* self) {
    if (!self->server) {
        return ERROR;
    }

    uint32_t len_msg_be = htonl(self->len_msg);
    server_send(self->server, (char*)&len_msg_be, BYTES_LEN);
    server_send(self->server, self->message, self->len_msg);
    return SUCCESS;
}

int server_message_create_answer(server_message_t* self, sudoku_t* sudoku) {
    self->len_msg = answer_server_create(self->message, sudoku);
    //La funcion devuelve la longitud del mensaje creado
    return SUCCESS;
}

int server_message_set_server(server_message_t* self, server_t* server) {
    self->server = server;
    return SUCCESS;
}

int server_message_init(server_message_t* self) {
    memset(self->message, 0, MAX_LEN_MSG * sizeof(char));
    self->server = NULL;
    self->len_msg = 0;
    return SUCCESS;
}

int server_message_release(server_message_t* self) {
    memset(self->message, 0, MAX_LEN_MSG * sizeof(char));
    self->server = NULL;
    self->len_msg = 0;
    return SUCCESS;
}
