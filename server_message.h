#ifndef _SERVER_MESSAGE_H_
#define _SERVER_MESSAGE_H_

#include "message.h"
#include "server.h"
#include "sudoku.h"

typedef struct server_message {
    message_t message;
    message_t len_msg;
    server_t* server;
} server_message_t;

int server_message_init(server_message_t* self);

int server_message_set_server(server_message_t* self, server_t* server);

int server_message_recv(server_message_t* self);

int server_message_send(server_message_t* self);

int server_message_create_answer(server_message_t* self, sudoku_t* sudoku);

#endif
