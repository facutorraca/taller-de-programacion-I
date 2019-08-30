#ifndef _PARSER_H_
#define _PARSER_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct parser {
    const char* delimiters;
    size_t max_line_length;
    char** words;
    FILE* file;
} parser_t;

int parser_init(parser_t* parser, const char* filename, char** words, const char* delimiter);

int parser_set_max_line_length(parser_t* parser, size_t max_line_length);

int parser_process_file(parser_t* parser);

#endif
