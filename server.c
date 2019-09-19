#define _POSIX_C_SOURCE 200112L

#include "server.h"
#include "socket.h"
#include "utils.h"
#include "interface.h"
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

int control_recv(char* msg);

int server_recv(server_t* server, char* msg, int (*control_recv)(char* msg)) {
    char frt_char;
    if (socket_receive(&server->s_socket, &frt_char, 1) < 0) {
        return ERROR;
    }
    msg[0] = frt_char;
    if (control_recv(msg) == ERROR) {
        if (socket_receive(&server->s_socket, msg, 3) < 0) {
            return ERROR;
        }
    }
    return SUCCESS;
}

int server_send(server_t* server, char* msg, uint32_t len_msg) {
    if (socket_send(&server->s_socket,(uint8_t*)msg, len_msg) > 0) {
        return SUCCESS;
    }
    return ERROR;
}

int server_listen(server_t* server) {
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
