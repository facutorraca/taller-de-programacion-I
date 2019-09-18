#define _POSIX_C_SOURCE 200112L

#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "client.h"
#include "socket.h"
#include "message.h"
#include "utils.h"

#define MAX_BUFFER 722

int control_recv(message_t* msg);

int client_recv(client_t* client, message_t* msg, uint32_t length_msg) {
    char buffer[MAX_BUFFER];
    if (socket_receive(&client->c_socket, buffer, length_msg) > 0) {
        message_append_string(msg, buffer, length_msg);
        return SUCCESS;
    }
    return ERROR;
}

int client_send(client_t* client, message_t* msg) {
    char* msg_buf = message_get(msg);
    if (socket_send(&client->c_socket,(uint8_t*)msg_buf,
                    message_get_length(msg)) > 0) {
        return SUCCESS;
    }
    return ERROR;
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

int client_release(client_t* client) {
    return socket_release(&client->c_socket);
}
