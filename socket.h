#ifndef _SOCKET_H_
#define _SOCKET_H_

typedef struct socket {
    int fd;
} socket_t;

int socket_init(socket_t* self);

int socket_bind(socket_t* self, const char* service);

int socket_connect(socket_t* self, const char* host, const char* service);

int socket_send(socket_t* self, const void* buffer, size_t length);

int socket_receive(socket_t* self, void* buffer, size_t length);

int socket_listen(socket_t* self);

int socket_release(socket_t* self);

#endif
