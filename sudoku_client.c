#include "sudoku_client.h"
#include "client_message.h"
#include "instruction.h"
#include "client.h"
#include "utils.h"

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

int sudoku_client_init(sudoku_client_t* self) {
    client_message_init(&self->client_msg);
    instruction_init(&self->instruction);
    return SUCCESS;
}

int sudoku_client_release(sudoku_client_t* self, client_t* client) {
    client_release(client);
    client_message_release(&self->client_msg);
    instruction_release(&self->instruction);
    return SUCCESS;
}

int sudoku_run_as_client(const char* host, const char* port) {
    sudoku_client_t sudoku_client;
    sudoku_client_init(&sudoku_client);

    client_t client;
    client_init(&client, host, port);
    client_connect_with_server(&client);
    client_message_set_client(&sudoku_client.client_msg,&client);

    sudoku_client_start_connection(&sudoku_client);
    sudoku_client_release(&sudoku_client, &client);
    return SUCCESS;
}
