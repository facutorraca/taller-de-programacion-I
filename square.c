#include <stdbool.h>
#include "square.h"

int get_box_number(int row, int col) {
    int box_row = row / 3;
    int box_col = col / 3;
    return (box_row * 3) + box_col;
}

int square_init(square_t* square, char number) {
    if (number != '0') {
        square->number = number;
        square->fixed = true;
    } else {
        square->number = ' ';
        square->fixed = false;
    }
    return SUCCESS;
}

int square_reset(square_t* square) {
    if (!square->fixed) {
        square->number = ' ';
    }
    return SUCCESS;
}

int square_put_number(square_t* square, char number) {
    if (square->fixed) {
        return ERROR;
    }
    square->number = number;
    return SUCCESS;
}

int square_set_box(square_t* square, int row, int col) {
    square->box = get_box_number(row, col);
    return SUCCESS;
}

int square_get_box(square_t* square) {
    return square->box;
}

char square_get_number(square_t* square) {
    return square->number;
}
