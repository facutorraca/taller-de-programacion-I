#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "socket.h"
#include "message.h"

int control_recv(message_t* msg);

int server_start_to_recv(server_t* server, message_t* msg, int (*control_recv)(message_t*) ) {
    char byte; //The message is capted byte by byte
    do {
        if(socket_receive(&server->s_socket, &byte, 1) == 1) {
            message_append_character(msg, byte);
        }
    } while (control_recv(msg) == ERROR);
    return SUCCESS;
}

int server_start_to_send(server_t* server, message_t* msg) {
    int bytes_sent = 0, total_bytes = 0;
    do {
        bytes_sent = socket_send(&server->s_socket, msg->buffer, msg->len_msg);
        total_bytes = bytes_sent + total_bytes;
    } while (msg->len_msg != total_bytes);
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
    socket_init(&server->s_socket);
    socket_init(&server->acceptor);
    server->port = port;
    return SUCCESS;
}
