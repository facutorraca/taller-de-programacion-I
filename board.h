#ifndef _BOARD_H_
#define _BOARD_H_

#define CANT_SQR 81
#define CANT_ROW 9
#define CANT_COL 9
#define CANT_BOX 9

#include <stdbool.h>
#include "square.h"

typedef struct board {
    square_t square[CANT_SQUARES];
    //row_t row[CANT_ROW];
    //box_t box[CANT_BOX];
    //column_t column[CANT_COL];
} board_t;

int board_init(board_t* board);

int board_reset();

int board_release();

int board_get_numbers(board_t* board, char* buffer);

int board_put_number(board_t* board, char num, char row, char col);

#endif
