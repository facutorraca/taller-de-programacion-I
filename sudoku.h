#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include "board.h"

typedef struct sudoku {
    board_t board;
} sudoku_t;

int sudoku_init(sudoku_t* sudoku);

int sudoku_get_board_numbers(sudoku_t* sudoku, char* buffer);

int sudoku_put_number(sudoku_t* sudoku, char num, char row, char col);

int board_put_number(board_t* board, char num, char row, char col);

#endif
