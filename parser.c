#include <string.h>
#include <stdio.h>
#include "parser.h"

#define SUCCESS 0
#define ERROR 1

int parser_process_line(char* line, parser_t* parser, int start_pos) {
    char* word = strtok(line, parser->delimiters);

    int words_added = 0;
    while (word != NULL) {
        parser->words[start_pos + words_added] = word;
        word = strtok(NULL, parser->delimiters);
        words_added++;
    }
    return words_added;
}

int parser_init(parser_t* parser, const char* filename, char** words, const char* delimiter) {
    parser->file = fopen(filename, "r");
    parser->max_line_length = 100;
    parser->words = words;
    parser->delimiters = delimiter;
    return SUCCESS;
}

int parser_set_max_line_length(parser_t* parser, size_t max_line_length) {
    parser->max_line_length = max_line_length;
    return SUCCESS;
}

int parser_process_file(parser_t* parser) {
    int start_pos = 0;

    //parser->max_line_length + 1  to read "\ņ"
    char line[parser->max_line_length];
    while (fgets(line, parser->max_line_length + 1, parser->file) != NULL) {
        int words_added = parser_process_line(line, parser, start_pos);
        start_pos = start_pos + words_added;
    }
    return SUCCESS;
}
