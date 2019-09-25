#include "acceptor_socket.h"
#include "socket.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>
#include <string>

#define ERROR -1
#define SUCCESS 0
#define INVALID_FD -1
#define MAX_PENDING_CONNECTIONS 10

/*--------------------------PUBLIC------------------------------*/
AcceptorSocket::AcceptorSocket(const std::string service):
    service(service)
{
    this->fd = INVALID_FD;
}

int AcceptorSocket::bind() {
    struct addrinfo *result;  //Pointer to the result list
    socket_getaddrinfo(&result, AI_PASSIVE);

    struct addrinfo *rst_iter = result;
    while (rst_iter) {
        this->fd = socket(rst_iter->ai_family,
                          rst_iter->ai_socktype,
                          rst_iter->ai_protocol);

        if (bind(this->fd, rst_iter->ai_addr, rst_iter->ai_addrlen) == SUCCESS) {
            freeaddrinfo(result);
            return SUCCESS;
        }
        close(this->fd);
        rst_iter = rst_iter->ai_next;
    }
    freeaddrinfo(result);
    std::cout << "Error en bind" << '\n'; //Cambiar esto!
    return ERROR;
}

int AcceptorSocket::listen() {
    if (listen(this->fd, MAX_PENDING_CONNECTIONS) == ERROR) {
        return ERROR;
    }
    return SUCCESS;
}

Socket SocketAcceptorSocket::accept() {
    int new_fd = accept(this->fd, NULL, NULL);
    Socket new_socket(new_fd);

    return std::move(new_socket);
}

/*--------------------------PRIVATE-----------------------------*/
AcceptorSocket::~AcceptorSocket();

int AcceptorSocket::socket_getaddrinfo(struct addrinfo** result, int ai_flags) {
    struct addrinfo hints; //Criteria for selecting the socket addr structures

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;        //IPv4
    hints.ai_socktype = SOCK_STREAM;  //TCP
    hints.ai_flags = ai_flags;        //AI_PASSIVE for server, 0 for client
    return getaddrinfo(NULL, service.c_str(), &hints, result);
}
