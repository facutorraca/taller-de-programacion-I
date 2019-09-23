#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "socket.h"

typedef struct client {
    const char* host;
    const char* port;
    socket_t c_socket;
} client_t;

//Recibe un mensaje si es posible y lo guarda en msg.
//PRE: self fue inicializado previamente. Msg fue inicializado
//previamente. Length contiene la longitud del mensaje esperado
int client_recv(client_t* self, char* msg, uint32_t length);

//Envia un mensaje si es posible.
//PRE: self fue inicializado previamente. Msg contiene
//el mensaje que quiere ser enviado, con longitud length
int client_send(client_t* client, char* msg, uint32_t length);

//Conecta al cliente con un servidor si posible
//PRE: self fue inicializado previamente.
int client_connect_with_server(client_t* client);

//Inicializa una instacia de client
//PRE: self apunta un sector válido de memoria. Host y port
//son un servicio y puerto valido respectivamente
int client_init(client_t* self, const char* host, const char* port);

//Inicializa una instacia de server
//PRE: self apunta un sector válido de memoria
int client_release(client_t* self);

#endif
