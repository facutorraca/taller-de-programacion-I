#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "socket.h"
#include "message.h"

#define ERROR 1
#define SUCCESS 0

int control_recv(message_t* msg);

int server_start_to_receive(server_t* server, message_t* msg, int (*control_recv)(message_t*) ) {
    char buffer[1]; //The message is capted byte by byte
    do {
        buffer[0] = 0;
        if(socket_receive(&server->s_socket, buffer, 1) == 1) {
            message_append_character(msg, buffer[0]);
        }
    } while (control_recv(msg) == ERROR);
    return SUCCESS;
}

int server_start_to_listen(server_t* server) {
    socket_bind(&server->acceptor, server->port);
    socket_listen(&server->acceptor);
    // Now process is in sleep mode waiting
    // for the incoming connection
    socket_accept(&server->acceptor, &server->s_socket, server->port);
    return SUCCESS;
}

int server_init(server_t* server, const char* port) {
    socket_init(&server->acceptor);
    socket_init(&server->s_socket);
    server->port = port;
    return SUCCESS;
}
