#ifndef _INSTRUCTION_H_
#define _INSTRUCTION_H_

#include <stdbool.h>

#define MAX_LEN_INS 20

typedef struct instruction {
    char instuction[MAX_LEN_INS];
} instruction_t;

//Devuelve true si la instruccion es un "get"
//PRE: self fue inicializado previamente.
bool instruction_is_get(instruction_t* self);

//Devuelve true si la instruccion es un "verify"
//PRE: self fue inicializado previamente.
bool instruction_is_verify(instruction_t* self);

//Devuelve true si la instruccion es un "reset"
//PRE: self fue inicializado previamente.
bool instruction_is_reset(instruction_t* self);

//Devuelve true si la instruccion es un "exit"
//PRE: self fue inicializado previamente.
bool instruction_is_exit(instruction_t* self);

//Devuelve la fila (si coincide) de la instruccion
//PRE: self fue inicializado previamente.
char instruction_get_row(instruction_t* self);

//Devuelve la columns (si coincide) de la instruccion
//PRE: self fue inicializado previamente.
char instruction_get_col(instruction_t* self);

//Devuelve el numero (si coincide) de la instruccion
//PRE: self fue inicializado previamente.
char instruction_get_num(instruction_t* self);

//Inicializa una instacia de instruction
//PRE: self apunta un sector válido de memoria
int instruction_init(instruction_t* self);

//Destruye una instacia de instruction
//PRE: self fue inicializado previamente.
int instruction_release(instruction_t* self);

//Obtiene un nueva instruccion de STDIN
//PRE: self fue inicializado previamente.
int instruction_get_new(instruction_t* self);

#endif
