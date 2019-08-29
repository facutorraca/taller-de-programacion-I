#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "server.h"
#include "socket.h"

#define ERROR -1
#define SUCCESS 0

int server_start(server_t* server) {
    socket_bind(&server->acceptor, server->port);
    socket_listen(&server->acceptor);

    // Now process is in sleep mode waiting
    // for the incoming connection

    socket_accept(&server->acceptor, &server->s_socket, server->port);

    // Here goes a while to receive and send messages

    return SUCCESS;
}


int server_init(const char* port) {
    //server initalized on the stack
    server_t server;
    socket_init(&server.acceptor);
    socket_init(&server.s_socket);
    server.port = port;

    //Memory direction of server
    return server_start(&server);
}
