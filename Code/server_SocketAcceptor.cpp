#include "server_SocketAcceptor.h"
#include "common_Socket.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <netdb.h>
#include <string>

#define ERROR -1
#define SUCCESS 0
#define INVALID_FD -1
#define MAX_PENDING_CONNECTIONS 10

/*--------------------------PUBLIC------------------------------*/
SocketAcceptor::SocketAcceptor() {
    this->fd = INVALID_FD;
}

int SocketAcceptor::bind(const std::string port) {
    struct addrinfo *result;  //Pointer to the result list

    struct addrinfo hints; //Criteria for selecting the socket addr structures
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;        //IPv4
    hints.ai_socktype = SOCK_STREAM;  //TCP
    hints.ai_flags = AI_PASSIVE;        //AI_PASSIVE for server, 0 for client
    getaddrinfo(nullptr, port.c_str(), &hints, &result);

    struct addrinfo *rst_iter = result;
    while (rst_iter) {
        this->fd = socket(rst_iter->ai_family,
                          rst_iter->ai_socktype,
                          rst_iter->ai_protocol);

        if (::bind(this->fd, rst_iter->ai_addr, rst_iter->ai_addrlen) == SUCCESS) {
            freeaddrinfo(result);
            return SUCCESS;
        }
        this->close(this->fd);
        rst_iter = rst_iter->ai_next;
    }
    freeaddrinfo(result);
    std::cout << "Error en bind" << '\n'; //Cambiar esto!
    return ERROR;
}

int SocketAcceptor::listen() {
    if (::listen(this->fd, MAX_PENDING_CONNECTIONS) == ERROR) {
        return ERROR;
    }
    return SUCCESS;
}

Socket SocketAcceptor::accept() {
    int new_fd = ::accept(this->fd, NULL, NULL);
    Socket new_socket(new_fd);

    return std::move(new_socket);
}

void SocketAcceptor::close() {
    if (this->fd != INVALID_FD) {
        ::close(this->fd);
        this->fd = INVALID_FD;
    }
}

/*--------------------------PRIVATE-----------------------------*/
SocketAcceptor::~SocketAcceptor() {
    if (this->fd != INVALID_FD) {
        this->close();
    }
}
