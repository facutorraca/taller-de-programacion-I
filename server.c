#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "server.h"
#include "socket.h"

#define ERROR -1
#define SUCCESS 0

int server_init(const char* port) {
    server_t server;
    server->port = port;
    server.acceptor = socket_init(&server.acceptor);
    server.connection = socket_init(&server.acceptor);

    server_start(&server);
}

int server_start(server_t* server) {
    socket_bind(&server.acceptor, server->port);
    socket_listen(&server.acceptor);

    bool server_running = true;
    while (server_running) {
        if (socket_accept(&accept, &new_connection, port) == ERROR) {
            printf("Accept failed\n");
            return ERROR;
        }
    }
}
