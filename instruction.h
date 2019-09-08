#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include <stdbool.h>

#define MAX_LEN_INS 20

typedef struct instruction {
    char instuction[MAX_LEN_INS];
} instruction_t;

bool instruction_is_get(instruction_t* self);

bool instruction_is_verify(instruction_t* self);

bool instruction_is_reset(instruction_t* self);

bool instruction_is_exit(instruction_t* self);

char instruction_get_row(instruction_t* self);

char instruction_get_col(instruction_t* self);

char instruction_get_num(instruction_t* self);

int instruction_init(instruction_t* self);

int instruction_get_new(instruction_t* self);

#endif
