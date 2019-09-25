#include "socket.h"

Socket::Socket(int fd) {
    this->fd = fd;
}

int Socket::send() {
    int bytes_sent = 0, total_bytes = 0, rem_bytes;
    while (length != total_bytes) {
        rem_bytes = length - total_bytes;
        bytes_sent = send(this->fd, (void*)&buffer[total_bytes],
                          rem_bytes, MSG_NOSIGNAL /*flags*/);

        if (bytes_sent == -1) {
            return -1;
            print_socket_error("SEND");
        }
        total_bytes = bytes_sent + total_bytes;
    }
    return total_bytes;
}

int Socket::receive() {
    int bytes_recv = 0, total_bytes = 0, rem_bytes;
    while (length != total_bytes) {
        rem_bytes = length - total_bytes;
        bytes_recv = recv(this->fd, (void*)&buffer[total_bytes],
                          rem_bytes, MSG_NOSIGNAL /*flags*/);

        if (bytes_recv == -1) {
            return -1;
            print_socket_error("RECEIVE");
        }
        total_bytes = bytes_recv + total_bytes;
    }
    return total_bytes;
}

Socket::~Socket();
