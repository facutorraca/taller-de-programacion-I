#include "parser.h"
#include <string.h>
#include <stdio.h>
#include "utils.h"

#define MAX_LINE_LENGTH 19

int parser_process_line(const char* line,
                        parser_t* parser,
                        char* buffer,
                        int buf_pos) {
    int chars_added = 0;
    for (int i = 0; i < 18; i++) {
        if (i % 2 == 0) {
            buffer[buf_pos + chars_added] = (char)line[i];
            chars_added++;
        }
    }
    return chars_added;
}

int parser_process_file(parser_t* parser, char* buffer) {
    int buf_pos = 0;
    //parser->max_line_length + 1  to read "\ņ"
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, parser->file) != NULL) {
        int chars_added = parser_process_line(line, parser, buffer, buf_pos);
        buf_pos = buf_pos + chars_added;
    }
    return SUCCESS;
}

int parser_init(parser_t* parser, const char* filename) {
    parser->file = fopen(filename, "r");
    return SUCCESS;
}

int parser_release(parser_t* parser) {
    fclose(parser->file);
    parser->file = NULL;
    return SUCCESS;
}
