#include "sudoku_server.h"
#include "server_message.h"
#include "sudoku.h"
#include "server.h"
#include <stdbool.h>

int sudoku_server_start_connection(sudoku_server_t* sudoku_server, server_t* server) {
    bool connected = true;
    while (connected) {
        if (server_message_recv(&sudoku_server->server_msg) == ERROR){
            connected = false;
        }
        if (connected) {
            server_message_create_answer(&sudoku_server->server_msg, &sudoku_server->sudoku);
            server_message_send(&sudoku_server->server_msg);
        }
    }
    server_release(server);
    return SUCCESS;
}

int sudoku_server_init(sudoku_server_t* sudoku_server) {
    sudoku_t sudoku;
    sudoku_init(&sudoku);

    server_message_t server_msg;
    server_message_init(&server_msg);

    sudoku_server->server_msg = server_msg;
    sudoku_server->sudoku = sudoku;
    return SUCCESS;
}

int sudoku_server_start(const char* port) {
    sudoku_server_t sudoku_server;
    sudoku_server_init(&sudoku_server);;

    server_t server;
    server_init(&server, port);
    server_listen(&server);
    server_message_set_server(&sudoku_server.server_msg, &server);

    sudoku_server_start_connection(&sudoku_server, &server);
    return SUCCESS;
}
