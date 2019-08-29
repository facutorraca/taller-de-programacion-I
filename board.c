#include <stdlib.h>
#include "board.h"

#define COLUMNS 9
#define ROWS 9

board_t* board_create() {
    board_t* board = (board_t*) malloc(sizeof(board_t));
    board->squares = (char*) malloc(COLUMNS * ROWS * sizeof(char));
    return board;
}
