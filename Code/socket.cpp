#include "socket.h"

#define ERROR -1
#define SUCCESS 0
#define INVALID_FD -1

/*--------------------------PUBLIC------------------------------*/
Socket::Socket() {
    self->fd = -1
}

Socket::Socket(int fd) {
    this->fd = fd;
}

int Socket::send(const char* msg, size_t len) {
    int bytes_sent = 0, total_bytes = 0, rem_bytes;
    while (len != total_bytes) {
        rem_bytes = length - total_bytes;
        bytes_sent = send(this->fd, (void*)&msg[total_bytes],
                          rem_bytes, MSG_NOSIGNAL /*flags*/);

        //Controlar bytes = 0
        if (bytes_sent == -1) {
            return -1;
        }
        total_bytes = bytes_sent + total_bytes;
    }
    return total_bytes;
}

int Socket::receive(char* buf, size_t len) {
    int bytes_recv = 0, total_bytes = 0, rem_bytes;
    while (length != total_bytes) {
        rem_bytes = length - total_bytes;
        bytes_recv = recv(this->fd, (void*)&buf[total_bytes],
                          rem_bytes, MSG_NOSIGNAL /*flags*/);

        //Controlar bytes = 0
        if (bytes_recv == -1) {
            return -1;
        }
        total_bytes = bytes_recv + total_bytes;
    }
    return total_bytes;
}

int Socket::connect() {
    struct addrinfo *result;  //Pointer to the result list
    socket_getaddrinfo(&result, service, 0);

    struct addrinfo *rst_iter = result;
    while (rst_iter) {
        this->fd = socket(rst_iter->ai_family,
                          rst_iter->ai_socktype,
                          rst_iter->ai_protocol);

        if (this->fd == -1) {
            freeaddrinfo(result);
            return ERROR;
        }

        if (connect(this->fd,
                    rst_iter->ai_addr,
                    rst_iter->ai_addrlen) == SUCCESS) {
            freeaddrinfo(result);
            return SUCCESS;
        }
        close(this->fd);
        rst_iter = rst_iter->ai_next;
    }
    freeaddrinfo(result);
    return ERROR;
}

/*--------------------------PRIVATE-----------------------------*/
Socket::~Socket();

int Socket::socket_getaddrinfo(struct addrinfo** result, int ai_flags) {
    struct addrinfo hints; //Criteria for selecting the socket addr structures

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;        //IPv4
    hints.ai_socktype = SOCK_STREAM;  //TCP
    hints.ai_flags = ai_flags;        //AI_PASSIVE for server, 0 for client
    return getaddrinfo(NULL, service.c_str(), &hints, result);
}
