#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "board.h"
#include "square.h"
#include "utils.h"
#include "interface.h"
#include "rules.h"

char* board_get_drawing(board_t* self) {
    return self->drawing;
}

int cmp_by_square(const void *sqr_a, const void *sqr_b) {
    int box_a = square_get_box((square_t*)sqr_a);
    int box_b = square_get_box((square_t*)sqr_b);
    return box_a - box_b;
}

//Funcion para simular una matriz en un vector
int get_board_position(int row, int col) {
    /*Para el input del usuario que es
     *de 1 a 9 */
    return (row - 1) * 9 + (col - 1);
}

//Funcion para simular una matriz en un vector
int get_line_pos(int row, int col) {
    /*Para el manejo interns con indices de
     *de 0 a 8 */
    return (row * 9) + col;
}

int update_drawing(board_t* self) {
    int pos_nbr;
    for (int i = 0; i < NUM_SQUARES; i++) {
        pos_nbr = self->pos_nbr[i];
        self->drawing[pos_nbr] = square_get_number(&self->square[i]);
    }
    return SUCCESS;
}

int board_put_number(board_t* self, char num, int row, int col) {
    int pos = get_board_position(row, col);
    if (square_put_number(&self->square[pos], num) == ERROR) {
        return ERROR;
    }
    update_drawing(self);
    return SUCCESS;
}

int board_reset(board_t* self) {
    for (int i = 0; i < NUM_SQUARES; i++) {
        square_reset(&self->square[i]);
    }
    update_drawing(self);
    return SUCCESS;
}

int sort_square_by_box(board_t* self, square_t* sqr_dup) {
    for (int i = 0; i < NUM_SQUARES; i++) {
        sqr_dup[i] = self->square[i];
    }
    qsort(sqr_dup, 81, sizeof(square_t), cmp_by_square);
    return SUCCESS;
}

int board_verify_row(board_t* self) {
    char line[9];
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            int pos = get_line_pos(row, col);
            line[col] = square_get_number(&self->square[pos]);
        }
        if (!line_is_correct(line)) {
            return ERROR;
        }
    }
    return SUCCESS;
}

int board_verify_col(board_t* self) {
    char line[9];
    for (int col = 0; col < 9; col++) {
        for (int row = 0; row < 9; row++) {
            int pos = get_line_pos(row, col);
            line[row] = square_get_number(&self->square[pos]);
        }
        if (!line_is_correct(line)) {
            return ERROR;
        }
    }
    return SUCCESS;
}

int board_verify_box(board_t* self) {
    square_t sqr_dup[NUM_SQUARES];
    /*Se ordenan los numeros por caja y se los maneja
     *Como si fueran una fila */
    sort_square_by_box(self, sqr_dup);

    char box[9];
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            int pos = get_line_pos(row, col);
            box[col] = square_get_number(&sqr_dup[pos]);
        }
        if (!line_is_correct(box)) {
            return ERROR;
        }
    }
    return SUCCESS;
}

int complete_squares(board_t* self, const char* numbers) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            int i = get_line_pos(row, col);
            square_init(&self->square[i], numbers[i]);
            square_set_box(&self->square[i], row, col);
        }
    }
    return SUCCESS;
}

int complete_drawing(board_t* self, const char* numbers) {
    get_board_drawing(self->drawing);
    int pos_cur_nbr = 0;
    for (int i = 0; i < SIZE_BOARD; i++) {
        if (self->drawing[i] == 'X') {
            self->drawing[i] = square_get_number(&self->square[pos_cur_nbr]);
            self->pos_nbr[pos_cur_nbr] = i;
            pos_cur_nbr++;
        }
    }
    return SUCCESS;
}

int board_init(board_t* self, char* numbers) {
    memset(self->drawing, 0, SIZE_BOARD * sizeof(char));
    memset(self->pos_nbr, 0, NUM_SQUARES * sizeof(int));

    complete_squares(self, numbers);
    complete_drawing(self, numbers);
    return SUCCESS;
}

int board_release(board_t* self) {
    memset(self->drawing, 0, SIZE_BOARD * sizeof(char));
    memset(self->pos_nbr, 0, NUM_SQUARES * sizeof(int));
    return SUCCESS;
}
