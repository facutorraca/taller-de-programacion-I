#ifndef _BOARD_H_
#define _BOARD_H_

#define NUM_SQUARES 81
#define SIZE_BOARD 722

#include <stdbool.h>
#include "square.h"

typedef struct board {
    square_t square[NUM_SQUARES];
    char drawing[SIZE_BOARD];
    int pos_nbr[NUM_SQUARES]; //Posicion de los numeros en el dibujo
} board_t;

//Inicializa una instacia de board con los numeros
//enviados por parametro
//PRE: self apunta un sector válido de memoria
int board_init(board_t* self, char* numbers);

//Resetea el tablero a su estado inicial
//PRE: self fue inicializado mediante board_init
int board_reset(board_t* self);

//Destruye la instancia del tablero
//PRE: self fue inicializado mediante board_init
int board_release(board_t* self);

//Coloca un numero en la posicion indicada si es posible
//PRE: self fue inicializado mediante board_int row, col y num
//pertenecen al intervalo [1,9]
int board_put_number(board_t* self, char num, int row, int col);

//Verifica si las columnas cumplen con las reglas
//PRE: self fue inicializado mediante board_init
int board_verify_col(board_t* self);

//Verifica si las filas cumplen con las reglas
//PRE: self fue inicializado mediante board_init
int board_verify_row(board_t* self);

//Verifica si los cuadrados cumplen con las reglas
//PRE: self fue inicializado mediante board_init
int board_verify_box(board_t* self);

//Se obtiene un puntero al inico del vector
//con el dibujo del tablero
//PRE: self fue inicializado mediante board_init
char* board_get_drawing(board_t* self);

#endif
