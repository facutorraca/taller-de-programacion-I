#define _POSIX_C_SOURCE 200112L

#include "socket.h"
#include <sys/socket.h>
#include <stdbool.h>

#define ERROR -1
#define SUCCESS 0
#define MAX_PENDING_CONNECTIONS 10

int socket_getaddrinfo(struct addrinfo *result, const char* service, int ai_flags) {
    struct addrinfo hints; //Criteria for selecting the socket address structures

    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;        //IPv4
    hints.ai_socktype = SOCK_STREAM;  //TCP
    hints.ai_flags = ai_flags;        //AI_PASSIVE for server, 0 for client
    return getaddrinfo(NULL, service, &hints, &result);
}

int socket_init(socket_t* self) {
    self->fd = -1;       //Initiaize file descriptor value
    return SUCCESS;
}

int socket_bind(socket_t* self, const char* service) {
    struct addrinfo *result;  //Pointer to the result list
    socket_getaddrinfo(&result, service, AI_PASSIVE);

    int check;
    while (result_pointer) {
        self->fd = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
        check = bind(self->fd, result->ai_addr, result->ai_addrlen);
        if (chek == SUCCESS) {
            return SUCCESS;
        }
        close(self->fd);
    }
    return ERROR;
}

int socket_listen(socket_t* self) {
    listen(self->fd, MAX_PENDING_CONNECTIONS);
}
