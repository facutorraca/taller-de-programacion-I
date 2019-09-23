#ifndef _PARSER_H_
#define _PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN_STR 25
#define MAX_DELIM 2

typedef struct parser {
    FILE* file;
    char* buff;
    int buf_len;
    int buf_pos;
} parser_t;

//Inicializa una instancia de parser con el archivo a parsear
//PRE: self apunta a una posicion valida de memoria. Si el archvio no existe
//devuelve error
int parser_init(parser_t* self, const char* filename, char* buf, int len_buf);

//Parsea el archivo y lo guarda en el buffer
//PRE: Parser fue inicializado, buffer tiene el tamano suficiente para
//guardar el archivo
int parser_process_file(parser_t* parser);

//Elimina la instancia del parser, liberando todos los recursos
//PRE: self fue inicializado previamente.
int parser_release(parser_t* parser);

#endif
