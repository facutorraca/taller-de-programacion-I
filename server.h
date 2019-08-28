#ifndef _SERVER_H_
#define _SERVER_H_

typedef struct server {
    socket_t acceptor;
} server_t

int server_init(const char* port);

#endif
