#include <stdbool.h>
#include "square.h"

int square_init(square_t* square, char number) {
    square->number = number;
    if (number != '0') {
        square->fixed = true;
    } else {
        square->fixed = false;
    }
    return SUCCESS;
}

int square_reset(square_t* square) {
    if (!square->fixed) {
        square->number = '0';
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

char square_get_number(square_t* square) {
    return square->number;
}
