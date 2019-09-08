#ifndef _CLIENT_MESSAGE_H_
#define _CLIENT_MESSAGE_H_

#include "message.h"
#include "client.h"
#include "instruction.h"

typedef struct client_message {
    message_t message;
    client_t* client;
} client_message_t;

int client_message_init(client_message_t* self);

int client_message_set_client(client_message_t* self, client_t* client);

int client_message_recv(client_message_t* self);

int client_message_send(client_message_t* self);

int client_message_show(client_message_t* self);

int client_message_create_question(client_message_t* self,
                                   instruction_t* instruction);

#endif
