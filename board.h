#ifndef _BOARD_H_
#define _BOARD_H_

#include <stdbool.h>

typedef struct square {
    char number;
    bool fixed;
} square_t;

typedef struct board {
    square_t* squares;
} board_t;

board_t* board_create();

int board_reset();

int board_destroy();

int board_get_numbers(board_t* board, char* buffer);

#endif
