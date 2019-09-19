#include "client_message.h"
#include "instruction.h"
#include "question_client.h"
#include "client.h"
#include "interface.h"
#include "utils.h"
#include <string.h>
#include <arpa/inet.h>

#define BYTES_LEN 4

uint32_t calculate_length_message(char* msg) {
    char array_with_length[BYTES_LEN];
    memset(array_with_length, 0, BYTES_LEN * sizeof(char));

    uint32_t len;
    memcpy(&len, msg, BYTES_LEN);
    return ntohl(len);
}

int client_message_send(client_message_t* self) {
    if (!self->client) {
        return ERROR;
    }
    client_send(self->client, self->message, self->len_msg);
    memset(self->message, 0, MAX_LEN_MSG * sizeof(char));
    return SUCCESS;
}

int client_message_recv(client_message_t* self) {
    client_recv(self->client, self->message, BYTES_LEN);
    self->len_msg = calculate_length_message(self->message);

    //Restart the message to receive the new one
    memset(self->message, 0, MAX_LEN_MSG * sizeof(char));
    client_recv(self->client,self->message, self->len_msg);
    return SUCCESS;
}

int client_message_show(client_message_t* self) {
    interface_print_message(self->message, self->len_msg);
    return SUCCESS;
}

int client_message_create_question(client_message_t* self,
                                   instruction_t* instruction) {
    //Restart the message to receive the new one
    memset(self->message, 0, MAX_LEN_MSG * sizeof(char));
    self->len_msg = question_client_create(self->message, instruction);
    return SUCCESS;
}

int client_message_set_client(client_message_t* self, client_t* client) {
    self->client = client;
    return SUCCESS;
}

int client_message_init(client_message_t* self) {
    memset(self->message, 0, MAX_LEN_MSG * sizeof(char));
    self->len_msg = 0;
    self->client = NULL;
    return SUCCESS;
}

int client_message_release(client_message_t* self) {
    memset(self->message, 0, MAX_LEN_MSG * sizeof(char));
    self->len_msg = 0;
    self->client = NULL;
    return SUCCESS;
}
