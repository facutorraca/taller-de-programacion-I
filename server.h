#ifndef _SERVER_H_
#define _SERVER_H_

#include <stdint.h>
#include "socket.h"
#include "message.h"


typedef struct server {
    const char* port;
    socket_t acceptor;
    socket_t s_socket;
} server_t;

//Recibe un mensaje si es posible y lo guarda en msg.
//PRE: self fue inicializado previamente. Msg fue inicializado
//previamente y control receive permite determinar cuando
//el mensaje fue completamente leido.
int server_recv(server_t* self, char* msg, int (*control_recv)(char* msg));

//Envia un mensaje si es posible.
//PRE: self fue inicializado previamente. Msg contiene
//el mensaje que quiere ser enviado
int server_send(server_t* self, char* msg,  uint32_t len_msg);

//Pone al server en escuhca para acetar una conexion
//PRE: self fue inicializado previamente.
int server_listen(server_t* self);

//Libera la instancia de server, liberando todos los recursos
//PRE: self fue inicializado previamente.
int server_release(server_t* self);

//Inicializa una instacia de server
//PRE: self apunta un sector válido de memoria
int server_init(server_t* self, const char* port);

#endif
