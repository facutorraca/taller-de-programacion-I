#include "common_Socket.h"
#include "common_SocketError.h"
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

/*--------------------------PUBLIC------------------------------*/
Socket::Socket() {
    this->fd = INVALID_FD;
}

Socket::Socket(int fd) {
    this->fd = fd;
}

Socket::Socket(Socket&& other) {
    this->fd = other.fd;
    other.fd = INVALID_FD;
}

void Socket::receive(std::string& buf) {
    int flag;
    char byte_buf;
    do {
        flag = recv(this->fd, (void*)&byte_buf, 1, MSG_NOSIGNAL);
        if (flag == 0 || flag == ERROR) {
            throw SocketError("Receive Failed");
        }
        buf.push_back(byte_buf);
    } while (byte_buf != '\n');
}

void Socket::send(const std::string& msg) {
    const char* msg_buf = reinterpret_cast<const char*>(msg.data());
    int msg_size = msg.length();

    int bytes_sent = 0, total_bytes = 0, rem_bytes = 0;
    while (total_bytes != msg_size) {
        rem_bytes = msg_size - total_bytes;
        bytes_sent = ::send(this->fd,
                            (void*)&msg_buf[total_bytes],
                            rem_bytes,
                            MSG_NOSIGNAL);

        if (bytes_sent == 0 || bytes_sent == ERROR) {
            throw SocketError("Send Failed");
        }
        total_bytes = total_bytes + bytes_sent;
    }
}

void Socket::connect(const std::string host, const std:: string port) {
    struct addrinfo *result = nullptr;  //Pointer to the result list

    struct addrinfo hints; //Criteria for selecting the socket addr structures
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;        //IPv4
    hints.ai_socktype = SOCK_STREAM;  //TCP
    hints.ai_flags = 0;        //AI_PASSIVE for server, 0 for client
    getaddrinfo(host.c_str(), port.c_str(), &hints, &result);

    if (!result) {
        throw SocketError("Get Address Info Failed");
    }

    struct addrinfo *rst_iter = result;
    while (rst_iter) {
        this->fd = socket(rst_iter->ai_family,
                          rst_iter->ai_socktype,
                          rst_iter->ai_protocol);

        if (this->fd == INVALID_FD) {
            freeaddrinfo(result);
            throw SocketError("Try to connect invalid socket");
        }

        if (::connect(this->fd,
                      rst_iter->ai_addr,
                      rst_iter->ai_addrlen) == SUCCESS) {
            freeaddrinfo(result);
            return;
        }
        ::close(this->fd);
        rst_iter = rst_iter->ai_next;
    }
    freeaddrinfo(result);
    throw SocketError("Connect Failed");
}

void Socket::close() {
    if (this->fd != INVALID_FD) {
        shutdown(this->fd, SHUT_RDWR);
        ::close(this->fd);
        this->fd = INVALID_FD;
    }
}

/*--------------------------PRIVATE-----------------------------*/
Socket::~Socket() {
    this->close();
}
