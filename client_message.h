#ifndef _CLIENT_MESSAGE_H_
#define _CLIENT_MESSAGE_H_

#include "client.h"
#include "instruction.h"

#define MAX_LEN_MSG 722

typedef struct client_message {
    char message[MAX_LEN_MSG];
    uint32_t len_msg;
    client_t* client;
} client_message_t;


//Inicializa una instacia de client_message
//PRE: self apunta un sector válido de memoria
int client_message_init(client_message_t* self);

//Se guarda la un puntero a la instancia de client para
//utilizar durante el envio y recepcion.
//PRE: self fue inicializado previamente.
//client fue previamente inicializado
int client_message_set_client(client_message_t* self, client_t* client);

//Recibe un mensaje del client si es posible.
//PRE: self fue inicializado previamente.
int client_message_recv(client_message_t* self);

//Envia un mensaje del client si es posible.
//PRE: self fue inicializado previamente.
int client_message_send(client_message_t* self);

//Muestra el mensaje almacenado por STDOUT
//PRE: self fue inicializado previamente y
//un un mensjae debe haber sido recibido previamente
int client_message_show(client_message_t* self);

//Crea un mensaje con el protocolo necesario para poder
//enviarse y poder ser interpretado
//PRE: self fue inicializado previamente.
int client_message_create_question(client_message_t* self,
                                   instruction_t* instruction);

//Destruye la instancia de client_message
//PRE: self fue inicializado previamente.
int client_message_release(client_message_t* self);

#endif
