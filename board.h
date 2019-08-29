#ifndef _SUDOKU_H_
#define _SUDOKU_H_

#include <stdbool.h>

typedef struct board {
    char* squares;
} board_t;

typedef struct square {
    char number;
    bool fixed;
} square_t;

board_t* board_create();

int board_reset();

int board_destroy();

#endif
