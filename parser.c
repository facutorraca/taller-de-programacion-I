#include <string.h>
#include <stdio.h>
#include "parser.h"

#define MAX_LINE_LENGTH 18
#define SUCCESS 0
#define ERROR 1

int parser_process_line(char* line, parser_t* parser, char* buffer, int start_pos) {
    char* word = strtok(line, " \n");
    int words_added = 0;
    while (word != NULL) {
        buffer[start_pos + words_added] = (char)*word;
        word = strtok(NULL, " \n");
        words_added++;
    }
    return words_added;
}

int parser_init(parser_t* parser, const char* filename) {
    parser->file = fopen(filename, "r");
    return SUCCESS;
}

int parser_process_file(parser_t* parser, char* buffer) {
    int start_pos = 0;
    //parser->max_line_length + 1  to read "\ņ"
    char line[MAX_LINE_LENGTH + 1];
    while (fgets(line, MAX_LINE_LENGTH + 1, parser->file) != NULL) {
        int words_added = parser_process_line(line, parser, buffer, start_pos);
        start_pos = start_pos + words_added;
    }
    return SUCCESS;
}

int parser_release(parser_t* parser) {
    fclose(parser->file);
    parser->file = NULL;
    return SUCCESS;
}
