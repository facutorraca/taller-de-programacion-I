#ifndef _BOARD_H_
#define _BOARD_H_

#define NUM_SQUARES 81
#define SIZE_BOARD 722

#include <stdbool.h>
#include "square.h"

typedef struct board {
    square_t square[NUM_SQUARES];
    char drawing[SIZE_BOARD];
    int pos_nbr[NUM_SQUARES];
} board_t;

int board_init(board_t* board);

int board_reset();

int board_release();

int board_get_numbers(board_t* board, char* buffer);

int board_put_number(board_t* board, char num, char row, char col);

int board_verify_col(board_t* board);

int board_verify_row(board_t* board);

int board_verify_box(board_t* board);

char* board_get_drawing(board_t* board);

#endif
