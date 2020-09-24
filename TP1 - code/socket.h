#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <stdlib.h>
#include <stdint.h>

typedef struct socket {
    int fd;
} socket_t;

//Inicializa una instacia de soket
//PRE: self apunta un sector válido de memoria
int socket_init(socket_t* self);

//Realiza un bind del socket
//PRE: self fue inicializado previamente.
int socket_bind(socket_t* self, const char* service);

//Conecta el socket con otro si posible
//PRE: self fue inicializado previamente.
int socket_connect(socket_t* self, const char* host, const char* service);

//Realiza el envio del contenido de buffer si posible
//PRE: self fue inicializado previamente. Buffer debe tener
//los datos que quieren ser enviados
int socket_send(socket_t* self, uint8_t* buffer, size_t length);

//Recibe,si posible, el contenido en el buffer
//PRE: self fue inicializado previamente.
int socket_receive(socket_t* self, char* buffer, size_t length);

//Acepta una conexion con otro socket
//PRE: self fue inicializado previamente.
int socket_accept(socket_t* acceptor, socket_t* s_socket, const char* service);

//Pone al socket en escuhca para acetar una conexion
//PRE: self fue inicializado previamente.
int socket_listen(socket_t* self);

//Destruye una instacia de socket, liberando los recursos
//PRE: self fue inicializado previamente.
int socket_release(socket_t* self);

#endif
