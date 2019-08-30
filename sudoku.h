#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include "board.h"

typedef struct sudoku {
    board_t* board;
} sudoku_t;

int sudoku_init(sudoku_t* sudoku);

#endif
