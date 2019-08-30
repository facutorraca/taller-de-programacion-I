#ifndef _SERVER_H_
#define _SERVER_H_

#include "sudoku_server.h"
#include "socket.h"

typedef struct server {
    const char* port;
    socket_t acceptor;
    socket_t s_socket;
} server_t;

int server_init(server_t* server, const char* port);

int server_start(sudoku_servet_t* sudoku_server);

#endif
