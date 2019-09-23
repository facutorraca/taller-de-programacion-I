#include "parser.h"
#include <string.h>
#include <stdio.h>

#define MAX_LINE_LENGTH 19
#define SUCCESS 0
#define ERROR 1

int parser_process_line(const char* line, parser_t* self) {
   int chars_added = 0, i = 0;

   const char* aux = line;
   while (*aux != '\n') {
       if (*aux != ' ') {
           self->buff[self->buf_pos + chars_added] = *aux;
           chars_added++;
       }
       i++;
       aux = &line[i];
   }
   return chars_added;
}

int parser_init(parser_t* self, const char* filename, char* buff, int len_buf) {
   self->file = fopen(filename, "r");
   if (!self->file) {
       return ERROR;
   }
   self->buff = buff;
   self->buf_pos = 0;
   self->buf_len = len_buf;
   return SUCCESS;
}

int parser_process_file(parser_t* self) {
   //parser->max_line_length + 1  to read "\ņ"
   char line[MAX_LINE_LENGTH + 1];
   while (fgets(line, MAX_LINE_LENGTH + 1, self->file) != NULL) {
       int chars_added = parser_process_line(line, self);
       self->buf_pos = self->buf_pos + chars_added;
   }
   return SUCCESS;
}

int parser_release(parser_t* self) {
   fclose(self->file);
   self->file = NULL;
   self->buff = NULL;
   self->buf_pos = 0;
   self->buf_len = 0;
   return SUCCESS;
}
