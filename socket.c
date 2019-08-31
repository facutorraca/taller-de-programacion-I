#define _POSIX_C_SOURCE 200112L

#include "socket.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>

#define ERROR 1
#define SUCCESS 0
#define MAX_PENDING_CONNECTIONS 10

#include <stdio.h>

int socket_getaddrinfo(struct addrinfo** result, const char* service, int ai_flags) {
    struct addrinfo hints; //Criteria for selecting the socket address structures

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;        //IPv4
    hints.ai_socktype = SOCK_STREAM;  //TCP
    hints.ai_flags = ai_flags;        //AI_PASSIVE for server, 0 for client
    return getaddrinfo(NULL, service, &hints, result);
}

int socket_init(socket_t* self) {
    self->fd = -1;       //Initiaize file descriptor value
    return SUCCESS;
}

int socket_bind(socket_t* self, const char* service) {
    struct addrinfo *result;  //Pointer to the result list
    socket_getaddrinfo(&result, service, AI_PASSIVE);

    while (result) {
        self->fd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
        if( bind(self->fd, result->ai_addr, result->ai_addrlen) == SUCCESS) {
            return SUCCESS;
        }
        close(self->fd);
        result = result->ai_next;
    }
    return ERROR;
}

int socket_listen(socket_t* self) {
    return listen(self->fd, MAX_PENDING_CONNECTIONS);
}

int socket_connect(socket_t* self, const char* host, const char* service) {
    struct addrinfo *result;  //Pointer to the result list
    socket_getaddrinfo(&result, service, 0);

    while (result) {
        self->fd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
        if( connect(self->fd, result->ai_addr, result->ai_addrlen) == SUCCESS) {
            return SUCCESS;
        }
        close(self->fd);
        result = result->ai_next;
    }
    return ERROR;
}

int socket_accept(socket_t* acceptor, socket_t* s_socket, const char* service) {
    //client_address and client_address_lenght is NULL because is not needed
    s_socket->fd = accept(acceptor->fd, NULL /*client_address*/, NULL /*client_address_lenght*/);
    return SUCCESS;
}

int socket_send(socket_t* self, const char* buffer, size_t length) {
    // Return total bytes sent
    return send(self->fd, (void*) buffer, length, 0 /*flags*/);
}

int socket_receive(socket_t* self, char* buffer, size_t length) {
    // Return total bytes received
    return recv(self->fd, (void*) buffer, length, 0 /*flags*/);
}
