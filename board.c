#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "board.h"
#include "square.h"
#include "parser.h"

#define SUCCESS 0
#define ERROR 1

int board_get_square_values(char* numbers) {
    parser_t parser;
    parser_init(&parser, "board.txt");
    parser_process_file(&parser, numbers);
    parser_release(&parser);
    return SUCCESS;
}

int board_get_position(char row, char col) {
    return (((row - '0') - 1) * 9 + (col - '0')) - 1;
}

int get_line_pos(int row, int col) {
    return (row * 9) + col;
}

int board_get_numbers(board_t* board, char* buffer) {
    for (int i = 0; i < CANT_SQUARES; i++) {
        buffer[i] = square_get_number(&board->square[i]);
    }
    return SUCCESS;
}

int board_put_number(board_t* board, char num, char row, char col) {
    int pos = board_get_position(row, col);
    return square_put_number(&board->square[pos], num);
}

int board_complete_squares(board_t* board) {
    char numbers[CANT_SQUARES];
    board_get_square_values(numbers);

    int i;
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            i = get_line_pos(row, col);
            square_init(&board->square[i], numbers[i]);
            square_set_box(&board->square[i], row, col);
        }
    }
    return SUCCESS;
}

int board_reset(board_t* board) {
    for (int i = 0; i < CANT_SQUARES; i++) {
        square_reset(&board->square[i]);
    }
    return SUCCESS;
}

int board_init(board_t* board) {
    board_complete_squares(board);
    return SUCCESS;
}

int cmp_by_number(const void *num_a, const void *num_b) {
    int int_a = *(char*)num_a - '0';
    int int_b = *(char*)num_b - '0';
    return int_a - int_b;
}

int cmp_by_square(const void *sqr_a, const void *sqr_b) {
    int box_a = square_get_box((square_t*)sqr_a);
    int box_b = square_get_box((square_t*)sqr_b);
    return box_a - box_b;
}

bool board_verify(char* numbers) {
    qsort(numbers, 9, sizeof(char), cmp_by_number);
    for (int i = 1; i < 9; i++) {
        if (numbers[i-1] == numbers[i] && numbers[i] != '0') {
            return false;
        }
    }
    return true;
}

int board_verify_row(board_t* board) {
    char line[9];
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            line[col] = square_get_number(&board->square[get_line_pos(row, col)]);
        }
        if (!board_verify(line)) {
            return ERROR;
        }
    }
    return SUCCESS;
}

int board_verify_col(board_t* board) {
    char line[9];
    for (int col = 0; col < 9; col++) {
        for (int row = 0; row < 9; row++) {
            line[row] = square_get_number(&board->square[get_line_pos(row, col)]);
        }
        if (!board_verify(line)) {
            return ERROR;
        }
    }
    return SUCCESS;
}

int board_sort_square_by_box(board_t* board, square_t* sqr_dup) {
    for (int i = 0; i < CANT_SQUARES; i++) {
        sqr_dup[i] = board->square[i];
    }
    qsort(sqr_dup, 81, sizeof(square_t), cmp_by_square);
    return SUCCESS;
}

int board_verify_box(board_t* board) {
    square_t sqr_dup[CANT_SQUARES];
    board_sort_square_by_box(board, sqr_dup);

    char box[9];
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            box[col] = square_get_number(&sqr_dup[get_line_pos(row, col)]);
        }
        if (!board_verify(box)) {
            return ERROR;
        }
    }
    return SUCCESS;
}
