#ifndef _BOARD_H_
#define _BOARD_H_

#define CANT_SQUARES 81

#include <stdbool.h>

typedef struct square {
    char number;
    bool fixed;
} square_t;

typedef struct board {
    square_t squares[CANT_SQUARES];
} board_t;

int board_init(board_t* board);

int board_reset();

int board_release();

int board_get_numbers(board_t* board, char* buffer);

int board_put_number(board_t* board, char num, char row, char col);

#endif
