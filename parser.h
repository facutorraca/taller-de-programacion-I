#ifndef _PARSER_H_
#define _PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LEN_STR 25
#define MAX_DELIM 2

typedef struct parser {
    char* delimiter[MAX_DELIM];
    char str[MAX_LEN_STR];
    size_t pos_str;
    FILE* file;
    bool end_reached;
    int num_delim;
} parser_t;

//Inicializa una instancia de parser
//PRE: self apunta a una posicion valida de memoria
int parser_init(parser_t* parser);

//Obtiene la siguiente palabra del elemento (archivo o string) parseado
//PRE: self fue inicializado y previamente se le seteo un string o un archivo
int parser_get_next_word(parser_t* self, char* buffer);

//Elimina la instancia del parser, liberando todos los recursos
//PRE: self fue inicializado previamente.
int parser_release(parser_t* parser);

//Setea un archivo para ser parseado
//PRE: self fue inicializado previamente. Un string no debe estar seteado
int parser_set_file(parser_t* self, const char* filename);

//Setea un string para ser parseado
//PRE: self fue inicializado previamente. Un archivo no debe estar seteado
int parser_set_string(parser_t* self, char* str, size_t len_str);

//Setea un delimitador si es posible (Maxima capaidad de 2)
//PRE: self fue inicializado previamente.
int parser_set_delimiter(parser_t* self, char* delimiter);

#endif
