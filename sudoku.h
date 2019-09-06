#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include "board.h"
#include "stdbool.h"

typedef struct sudoku {
    board_t board;
} sudoku_t;

int sudoku_init(sudoku_t* sudoku);

char* sudoku_get_board_drawing(sudoku_t* sudoku);

int sudoku_put_number(sudoku_t* sudoku, char num, char row, char col);

int sudoku_reset(sudoku_t* sudoku);

int sudoku_verify(sudoku_t* sudoku);

bool sudoku_number_is_valid(int number);

bool sudoku_position_is_valid(int row, int col);

#endif
