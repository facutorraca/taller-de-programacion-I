#include "client.h"
#include "socket.h"

#define ERROR -1
#define SUCCESS 0

int client_init(const char* host, const char* port) {
    socket_t client;
    socket_init(&client);
    socket_connect(&client, host, port);
}
