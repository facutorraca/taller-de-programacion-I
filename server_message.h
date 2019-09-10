#ifndef _SERVER_MESSAGE_H_
#define _SERVER_MESSAGE_H_

#include "message.h"
#include "server.h"
#include "sudoku.h"

typedef struct server_message {
    message_t message;
    message_t len_msg;
    server_t* server;
} server_message_t;

//Inicializa una instacia de server_message
//PRE: self apunta un sector válido de memoria
int server_message_init(server_message_t* self);

//Se guarda la un puntero a la instancia de server para
//utilizar durante el envio y recepcion.
//PRE: self fue inicializado previamente.
//server fue previamente inicializado
int server_message_set_server(server_message_t* self, server_t* server);

//Recibe un mensaje del server si es posible.
//PRE: self fue inicializado previamente.
int server_message_recv(server_message_t* self);

//Envia un mensaje del server si es posible.
//PRE: self fue inicializado previamente.
int server_message_send(server_message_t* self);

//Crea un mensaje con el protocolo necesario para poder
//enviarse y poder ser interpretado
//PRE: self fue inicializado previamente.
int server_message_create_answer(server_message_t* self, sudoku_t* sudoku);

//Destruye la instancia de server_message
//PRE: self fue inicializado previamente.
int server_message_release(server_message_t* self);

#endif
