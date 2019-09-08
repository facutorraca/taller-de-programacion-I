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

int parser_init(parser_t* parser);

int parser_get_next_word(parser_t* self, char* buffer);

int parser_release(parser_t* parser);

int parser_set_file(parser_t* self, const char* filename);

int parser_set_string(parser_t* self, char* str, size_t len_str);

int parser_set_delimiter(parser_t* self, char* delimiter);

#endif
