#include <stdbool.h>
#include "square.h"
#include "utils.h"

int get_box_number(int row, int col) {
    int box_row = row / 3;
    int box_col = col / 3;
    return (box_row * 3) + box_col;
}

int square_init(square_t* self, char number) {
    if (number != '0') {
        self->number = number;
        self->fixed = true;
    } else {
        self->number = ' ';
        self->fixed = false;
    }
    return SUCCESS;
}

int square_reset(square_t* self) {
    if (!self->fixed) {
        self->number = ' ';
    }
    return SUCCESS;
}

int square_put_number(square_t* self, char number) {
    if (self->fixed) {
        return ERROR;
    }
    self->number = number;
    return SUCCESS;
}

int square_set_box(square_t* self, int row, int col) {
    self->box = get_box_number(row, col);
    return SUCCESS;
}

int square_get_box(square_t* self) {
    return self->box;
}

char square_get_number(square_t* self) {
    return self->number;
}

int square_release(square_t* self) {
    self->number = -1;
    self->fixed = false;
    return SUCCESS;
}
