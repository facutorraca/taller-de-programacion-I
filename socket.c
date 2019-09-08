#define _POSIX_C_SOURCE 200112L

#include "socket.h"
#include "utils.h"
#include "interface.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <stdbool.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <stdint.h>


#define MAX_PENDING_CONNECTIONS 10

int socket_getaddrinfo(struct addrinfo** result,
                       const char* service,
                       int ai_flags) {
    struct addrinfo hints; //Criteria for selecting the socket addr structures

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;        //IPv4
    hints.ai_socktype = SOCK_STREAM;  //TCP
    hints.ai_flags = ai_flags;        //AI_PASSIVE for server, 0 for client
    return getaddrinfo(NULL, service, &hints, result);
}

int socket_init(socket_t* self) {
    self->fd = -1; //Initiaize file descriptor value
    return SUCCESS;
}

int socket_bind(socket_t* self, const char* service) {
    struct addrinfo *result;  //Pointer to the result list
    int flag = socket_getaddrinfo(&result, service, AI_PASSIVE);
    if (flag == -1) {
        print_getaddrinfo_error(flag);
        return ERROR;
    }

    while (result) {
        self->fd = socket(result->ai_family,
                          result->ai_socktype,
                          result->ai_protocol);

        if (bind(self->fd, result->ai_addr, result->ai_addrlen) == SUCCESS) {
            freeaddrinfo(result);
            return SUCCESS;
        }
        close(self->fd);
        result = result->ai_next;
        print_socket_error("BIND");
    }
    freeaddrinfo(result);
    return ERROR;
}

int socket_listen(socket_t* self) {
    if (listen(self->fd, MAX_PENDING_CONNECTIONS) == -1) {
        print_socket_error("LISTEN");
        return ERROR;
    }
    return SUCCESS;
}

int socket_connect(socket_t* self, const char* host, const char* service) {
    struct addrinfo *result;  //Pointer to the result list
    socket_getaddrinfo(&result, service, 0);

    self->fd = socket(result->ai_family,
                      result->ai_socktype,
                      result->ai_protocol);
    while (result) {
        self->fd = socket(result->ai_family,
                          result->ai_socktype,
                          result->ai_protocol);
        if (connect(self->fd, result->ai_addr, result->ai_addrlen) == SUCCESS) {
            freeaddrinfo(result);
            return SUCCESS;
        }
        close(self->fd);
        result = result->ai_next;
        print_socket_error("CONNECT");
    }
    freeaddrinfo(result);
    return ERROR;
}

int socket_accept(socket_t* acceptor, socket_t* s_socket, const char* service) {
    //client_address and client_address_lenght is NULL because is not needed
    s_socket->fd = accept(acceptor->fd, NULL, NULL);
    if (s_socket->fd == -1) {
        print_socket_error("ACCEPT");
        return ERROR;
    }
    return SUCCESS;
}

int socket_send(socket_t* self, uint8_t* buffer, size_t length) {
    int total_bytes = send(self->fd, (void*) buffer, length, 0 /*flags*/);
    if (total_bytes == -1) {
        print_socket_error("SEND");
    }
    return total_bytes;
}

int socket_receive(socket_t* self, char* buffer, size_t length) {
    int total_bytes = recv(self->fd, (void*) buffer, length, 0 /*flags*/);
    if (total_bytes == -1) {
        print_socket_error("RECV");
    }
    return total_bytes;
}

int socket_release(socket_t* socket) {
    if (close(socket->fd) == -1) {
        print_socket_error("CLOSE");
        return ERROR;
    }
    return SUCCESS;
}
