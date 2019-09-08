#include "client_message.h"
#include "instruction.h"
#include "question_client.h"
#include "message.h"
#include "client.h"
#include "utils.h"
#include <string.h>
#include <arpa/inet.h>

#define BYTES_LEN 4

static uint32_t calculate_length_message(message_t* msg) {
    char array_with_length[BYTES_LEN];
    memset(array_with_length, 0, BYTES_LEN * sizeof(char));

    message_get_nfirst(msg, array_with_length, BYTES_LEN);
    return ntohl(array_to_uint(array_with_length));
}

int client_message_send(client_message_t* self) {
    if (!self->client) {
        return ERROR;
    }
    client_send(self->client, &self->message);
    message_init(&self->message); //Restart the message
    return SUCCESS;
}

int client_message_recv(client_message_t* self) {
    client_recv(self->client, &self->message, BYTES_LEN);
    uint32_t length_next_message = calculate_length_message(&self->message);

    message_init(&self->message); //Restart the message to receive the new one
    client_recv(self->client, &self->message, length_next_message);
    return SUCCESS;
}

int client_message_show(client_message_t* self) {
    return message_print(&self->message);
}

int client_message_create_question(client_message_t* self,
                                   instruction_t* instruction) {
    message_init(&self->message); //Restart the message to receive the new one
    return question_client_create(&self->message, instruction);
}

int client_message_set_client(client_message_t* self, client_t* client) {
    self->client = client;
    return SUCCESS;
}

int client_message_init(client_message_t* self) {
    message_init(&self->message);
    self->client = NULL;
    return SUCCESS;
}
