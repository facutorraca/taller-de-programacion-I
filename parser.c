#include "parser.h"
#include <string.h>
#include <stdio.h>
#include "utils.h"

bool pointer_is_before(char* ptr_a, char* ptr_b) {
    if (!ptr_a) {
        return false;
    }
    if (!ptr_b) {
        return true;
    }
    return ((ptr_b - ptr_a) > 0);
}

int increase_position(parser_t* self, char* end, size_t len_delim) {
    size_t pos = self->pos_str + (end - &self->str[self->pos_str]) + len_delim;
    if (pos >= strlen(self->str)) {
        return ERROR;
    }
    self->pos_str = pos;
    return SUCCESS;
}

int get_new_line(parser_t* self) {
    self->pos_str = 0;
    if (!fgets(self->str, MAX_LEN_STR, self->file)) {
        self->end_reached = true;
    }
    return SUCCESS;
}

int copy_in_buffer(parser_t* self, char* buff, char* end, size_t len_delim) {
    if (!end) {
        int len_str = strlen(self->str) - self->pos_str;
        strncpy(buff, &self->str[self->pos_str], len_str);
        get_new_line(self);
    } else {
        int len_str = end - &self->str[self->pos_str];
        strncpy(buff, &self->str[self->pos_str], len_str);
        if (increase_position(self, end, len_delim) == ERROR) {
            get_new_line(self);
        }
    }
    return SUCCESS;
}

int parser_get_next_word(parser_t* self, char* buffer) {
    if (self->end_reached) {
        return ERROR;
    }

    char* end_a = strstr(&self->str[self->pos_str], self->delimiter[0]);
    char* end_b = strstr(&self->str[self->pos_str], self->delimiter[1]);

    if (!end_a && !end_b) {
        copy_in_buffer(self, buffer, NULL, 0);
    } else if (pointer_is_before(end_a, end_b)) {
        copy_in_buffer(self, buffer, end_a, 1);
    } else { /* end_2 before end_1 */
        copy_in_buffer(self, buffer, end_b, 1);
    }
    return SUCCESS;
}

int parser_set_delimiter(parser_t* self, char* delimiter) {
    if (self->num_delim >= MAX_DELIM) {
        return ERROR;
    }
    self->delimiter[self->num_delim] = delimiter;
    self->num_delim++;
    return SUCCESS;
}

int parser_set_string(parser_t* self, char* str, size_t len_str) {
    if (len_str > MAX_LEN_STR) {
        return ERROR;
    }
    strncpy(self->str, str, len_str);
    return SUCCESS;
}

int parser_set_file(parser_t* self, const char* filename) {
    self->file = fopen(filename, "r");
    if (!self->file) {
        return ERROR;
    }
    //Init the line
    get_new_line(self);
    return SUCCESS;
}

int parser_init(parser_t* self) {
    memset(self->str, 0, MAX_LEN_STR * sizeof(char));
    memset(self->delimiter, 0, MAX_DELIM * sizeof(char*));
    self->pos_str = 0;
    self->file = NULL;
    self->end_reached = false;
    self->num_delim = 0;
    return SUCCESS;
}

int parser_release(parser_t* self) {
    if (self->file) {
        fclose(self->file);
        self->file = NULL;
    }
    return SUCCESS;
}
