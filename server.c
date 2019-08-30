#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "socket.h"

#define ERROR -1
#define SUCCESS 0

int server_start_to_receive(server_t* server) {
    char buffer[4] = {0};   //Initialize buffer

    bool continue_receiving = true;
    while(continue_receiving) {
        socket_receive(&server->s_socket, buffer, 4);
    }
    return SUCCESS;
}

int server_start(server_t* server) {
    socket_bind(&server->acceptor, server->port);
    socket_listen(&server->acceptor);

    // Now process is in sleep mode waiting
    // for the incoming connection

    socket_accept(&server->acceptor, &server->s_socket, server->port);
    server_start_to_receive(server);

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
