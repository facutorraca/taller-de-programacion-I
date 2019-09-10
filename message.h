#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <stdint.h>
#include <stdbool.h>

#define MAX_LEN_MSG 722

typedef struct message {
    char buffer[MAX_LEN_MSG];
    uint32_t len_msg;
} message_t;

//Inicializa una instancia de message
//PRE: self apunta a una posicion valida de memoria
int message_init(message_t* self);

//Crea un mensjae con el string pasado
//PRE: self fue inicializado previamente. El tamano del string
//coince con el pasado por parametro
int message_create(message_t* self, const char* str, uint32_t len);

//Agrega un caracter al final del mensaje
//PRE: self fue inicializado previamente.
int message_append_character(message_t* self, char character);

//Devuelve la longitud del mensaje
//PRE: self fue inicializado previamente.
uint32_t message_get_length(message_t* self);

//Devuelve el primer caracter del mensaje
//PRE: self fue inicializado previamente.
char message_get_first_character(message_t* self);

//Devulve en el buffer los primeros n caracteres del mensaje
//PRE: self fue inicializado previamente. El tamano del buffer
//coince con el pasado por parametro
int message_get_nfirst(message_t* self, char* buffer, int n);

//Apendea un string al final del mensaje
//PRE: self fue inicializado previamente. El tamano del string
//coince con el pasado por parametro
int message_append_string(message_t* self, char* str, int len);

//Imprimer el mensaje por STDOUT
//PRE: self fue inicializado previamente.
int message_print(message_t* self);

//Devuelve un puntero a la primera posicion del vector
//que contiene el mensaje
//PRE: self fue inicializado previamente.
char* message_get(message_t* self);

//Destruye la instancia de message
//PRE: self fue inicializado previamente
int message_release(message_t* self);

#endif
