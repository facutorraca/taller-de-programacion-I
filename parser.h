#ifndef _PARSER_H_
#define _PARSER_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct parser {
    FILE* file;
} parser_t;

int parser_init(parser_t* parser, const char* filename);

int parser_process_file(parser_t* parser, char* buffer);

#endif
