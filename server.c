#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "sudoku_server.h"
#include "server.h"
#include "socket.h"

#define ERROR -1
#define SUCCESS 0

int server_start_to_receive(sudoku_server_t* sudoku_server) {
    char buffer[4] = {0};   //Initialize buffer

    int bytes_recv = 0, total_bytes = 0;
    do {
        bytes_recv = socket_receive(&sudoku_server->server->s_socket, buffer, 4);
        total_bytes = bytes_recv + total_bytes;
    } while (sudoku_server_receive(sudoku_server, buffer, total_bytes) == ERROR) {
    return SUCCESS;
}

int server_start(sudoku_server_t* sudoku_server) {
    server_t server = sudoku_server->server;
    socket_bind(&server->acceptor, server->port);
    socket_listen(&server->acceptor);

    // Now process is in sleep mode waiting
    // for the incoming connection

    socket_accept(&server->acceptor, &server->s_socket, server->port);
    server_start_to_receive(server);

    return SUCCESS;
}

int server_init(server_t* server, const char* port) {
    //server initalized on the stack
    server_t server;
    socket_init(&server.acceptor);
    socket_init(&server.s_socket);
    server.port = port;

    return SUCCESS;
}
