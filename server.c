#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "server.h"
#include "socket.h"
#include "message.h"
#include "interface.h"

int control_recv(message_t* msg);

int server_start_to_recv(server_t* server, message_t* msg, int (*control_recv)(message_t*) ) {
    char buffer[MAX_BUFFER];
    int total_bytes = 0, bytes_recv = 0;
    do {
        bytes_recv = socket_receive(&server->s_socket, &buffer[total_bytes], MAX_BUFFER - total_bytes);
        message_append_string(msg, &buffer[total_bytes], bytes_recv);
        total_bytes = total_bytes + bytes_recv;
    } while (control_recv(msg) == ERROR);
    return total_bytes;
}

int server_start_to_send(server_t* server, message_t* msg) {
    int bytes_sent = 0, total_bytes = 0;
    do {
        bytes_sent = socket_send(&server->s_socket, (uint8_t*)&msg->buffer[total_bytes], message_get_length(msg) - total_bytes);
        total_bytes = bytes_sent + total_bytes;
    } while (msg->len_msg != total_bytes);
    return total_bytes;
}

int server_start_to_listen(server_t* server) {
    if(socket_bind(&server->acceptor, server->port) != SUCCESS) {
        print_binding_error();
    }
    if(socket_listen(&server->acceptor) != SUCCESS) {
        print_listening_error();
    }
    // Now process is in sleep mode waiting
    // for the incoming connection
    return socket_accept(&server->acceptor, &server->s_socket, server->port);
}

int server_init(server_t* server, const char* port) {
    socket_init(&server->s_socket);
    socket_init(&server->acceptor);
    server->port = port;
    return SUCCESS;
}

int server_release(server_t* server) {
    socket_release(&server->s_socket);
    socket_release(&server->acceptor);
    return SUCCESS;
}
