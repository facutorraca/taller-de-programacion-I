#include "server.h"
#include "socket.h"
#include "utils.h"
#include "message.h"
#include "interface.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_BUFFER 723

int control_recv(message_t* msg);

int server_recv(server_t* server,
                message_t* msg,
                int (*control_recv)(message_t* msg)) {
    char buffer[MAX_BUFFER];
    int total_bytes = 0, bytes_recv = 0, rem_bytes;
    do {
        rem_bytes = MAX_BUFFER - total_bytes;
        bytes_recv = socket_receive(&server->s_socket,
                                    &buffer[total_bytes],
                                    rem_bytes);
        message_append_string(msg, &buffer[total_bytes], bytes_recv);
        total_bytes = total_bytes + bytes_recv;
    } while (control_recv(msg) == ERROR);
    return total_bytes;
}

int server_send(server_t* server, message_t* msg) {
    char* msg_buf = message_get(msg);
    int bytes_sent = 0, total_bytes = 0, rem_bytes;
    while (message_get_length(msg) != total_bytes) {
        rem_bytes = message_get_length(msg) - total_bytes;
        bytes_sent = socket_send(&server->s_socket,
                                 (uint8_t*)&msg_buf[total_bytes],
                                 rem_bytes);
        total_bytes = bytes_sent + total_bytes;
    }
    return total_bytes;
}

int server_listen(server_t* server) {
    socket_setsockopt(&server->acceptor);
    socket_bind(&server->acceptor, server->port);
    socket_listen(&server->acceptor);
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
