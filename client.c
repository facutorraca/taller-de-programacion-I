#include "client.h"
#include "message.h"
#include "socket.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include <sys/socket.h>
#include <sys/types.h>

#define ERROR 1
#define SUCCESS 0

int client_start_to_send(client_t* client, message_t msg) {
    int bytes_sent = 0, total_bytes = 0;
    do {
        bytes_sent = socket_send(&client->c_socket, msg.buffer, msg.len_msg);
        total_bytes = bytes_sent + total_bytes;
    } while (msg.len_msg != total_bytes);
    return SUCCESS;
}

int client_connect_with_server(client_t* client) {
    socket_connect(&client->c_socket, client->host, client->port);
    return SUCCESS;
}

int client_init(client_t* client, const char* host, const char* port) {
    socket_init(&client->c_socket);
    client->host = host;
    client->port = port;

    return SUCCESS;
}
