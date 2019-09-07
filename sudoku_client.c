#include "sudoku_client.h"
#include "instruction.h"
#include "utils.h"
#include "message.h"
#include "client.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int sudoku_client_start_connection(sudoku_client_t* self) {
    while (instruction_get_new(&self->instruction) == SUCCESS  &&
           !instruction_is_exit(&self->instruction)) {

        client_message_create_question(&self->client_msg, &self->instruction);
        client_message_send(&self->client_msg);
        client_message_recv(&self->client_msg);
        client_message_show(&self->client_msg);
    }
    return SUCCESS;
}

int sudoku_client_init(sudoku_client_t* sudoku_client) {
    client_message_init(&sudoku_client->client_msg);
    instruction_init(&sudoku_client->instruction);
    return SUCCESS;
}

int sudoku_client_start(const char* host, const char* port) {
    sudoku_client_t sudoku_client;
    sudoku_client_init(&sudoku_client);

    client_t client;
    client_init(&client, host, port);
    client_connect_with_server(&client);
    client_message_set_client(&sudoku_client.client_msg,&client);

    sudoku_client_start_connection(&sudoku_client);
    client_release(&client);
    return SUCCESS;
}
