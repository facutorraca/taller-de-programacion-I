#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include "board.h"
#include "stdbool.h"

typedef struct sudoku {
    parset_t parser;
    board_t board;
} sudoku_t;

//Inicializa una instacia de suoku
//PRE: self apunta un sector válido de memoria
int sudoku_init(sudoku_t* sudoku);

//Se obtiene un puntero al inicio del vector
//con el dibujo del tablero
//PRE: self fue inicializado previamente.
char* sudoku_get_board_drawing(sudoku_t* sudoku);

//Coloca un numero en la posicion indicada si es posible
//PRE: self fue inicializado previamente. Row, col y num
//pertenecen al intervalo [1,9]
int sudoku_put_number(sudoku_t* sudoku, char num, char row, char col);

//Resetea el juego a su estado inicial
//PRE: self fue inicializado previamente.
int sudoku_reset(sudoku_t* sudoku);

//Verifica si el juego cumple con las reglas
//PRE: self fue inicializado previamente.
int sudoku_verify(sudoku_t* sudoku);

//Destruye la instancia del sudoku
//PRE: self fue inicializado mediante board_init
int sudoku_release(sudoku_t* sudoku);

#endif
