#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "socket.h"

#define ERROR 1
#define SUCCESS 0

int receive_control(const char* buffer, int total_bytes);

int server_start_to_receive(server_t* server, int (*receive_control)(const char*, int)) {
    char buffer[4] = {0};   //Initialize buffer

    int bytes_recv = 0, total_bytes = 0;
    do {
        bytes_recv = socket_receive(&server->s_socket, buffer, 4);
        total_bytes = bytes_recv + total_bytes;
    } while ( false /*receive_control(buffer, total_bytes ) == ERROR*/ );
    printf("%i\n", bytes_recv);
    printf("%s\n", buffer);
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
