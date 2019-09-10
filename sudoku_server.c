#include "sudoku_server.h"
#include "server_message.h"
#include "sudoku.h"
#include "server.h"
#include "utils.h"
#include <stdbool.h>

int sudoku_server_start_connection(sudoku_server_t* self) {
    bool connected = true;
    while (connected) {
        if (server_message_recv(&self->server_msg) == ERROR){
            connected = false;
        }
        if (connected) {
            server_message_create_answer(&self->server_msg, &self->sudoku);
            server_message_send(&self->server_msg);
        }
    }

    return SUCCESS;
}

int sudoku_server_init(sudoku_server_t* self) {
    sudoku_t sudoku;
    sudoku_init(&sudoku);

    server_message_t server_msg;
    server_message_init(&server_msg);

    self->server_msg = server_msg;
    self->sudoku = sudoku;
    return SUCCESS;
}

int sudoku_server_release(sudoku_server_t* self, server_t* server) {
    server_release(server);
    server_message_release(&self->server_msg);
    sudoku_release(&self->sudoku);
    return SUCCESS;
}

int sudoku_run_as_server(const char* port) {
    sudoku_server_t sudoku_server;
    sudoku_server_init(&sudoku_server);;

    server_t server;
    server_init(&server, port);
    server_listen(&server);
    server_message_set_server(&sudoku_server.server_msg, &server);

    sudoku_server_start_connection(&sudoku_server);
    sudoku_server_release(&sudoku_server, &server);
    return SUCCESS;
}
