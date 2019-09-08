#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "board.h"
#include "square.h"
#include "parser.h"
#include "utils.h"
#include "interface.h"
#include "rules.h"

#define SUCCESS 0
#define ERROR 1


char* board_get_drawing(board_t* board) {
    return board->drawing;
}

int cmp_by_square(const void *sqr_a, const void *sqr_b) {
    int box_a = square_get_box((square_t*)sqr_a);
    int box_b = square_get_box((square_t*)sqr_b);
    return box_a - box_b;
}

int get_board_position(char row, char col) {
    //Use for user input
    return (char_to_int(row) - 1) * 9 + (char_to_int(col) - 1);
}

int get_line_pos(int row, int col) {
    return (row * 9) + col;
}

int update_drawing(board_t* board) {
    int pos_nbr;
    for (int i = 0; i < 81; i++) {
        pos_nbr = board->pos_nbr[i];
        board->drawing[pos_nbr] = square_get_number(&board->square[i]);
    }
    return SUCCESS;
}

int board_put_number(board_t* board, char num, char row, char col) {
    int pos = get_board_position(row, col);
    if (square_put_number(&board->square[pos], num) == ERROR) {
        return ERROR;
    }
    update_drawing(board);
    return SUCCESS;
}

int board_reset(board_t* board) {
    for (int i = 0; i < NUM_SQUARES; i++) {
        square_reset(&board->square[i]);
    }
    update_drawing(board);
    return SUCCESS;
}

int sort_square_by_box(board_t* board, square_t* sqr_dup) {
    for (int i = 0; i < NUM_SQUARES; i++) {
        sqr_dup[i] = board->square[i];
    }
    qsort(sqr_dup, 81, sizeof(square_t), cmp_by_square);
    return SUCCESS;
}

int board_verify_row(board_t* board) {
    char line[9];
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            int pos = get_line_pos(row, col);
            line[col] = square_get_number(&board->square[pos]);
        }
        if (!line_is_correct(line)) {
            return ERROR;
        }
    }
    return SUCCESS;
}

int board_verify_col(board_t* board) {
    char line[9];
    for (int col = 0; col < 9; col++) {
        for (int row = 0; row < 9; row++) {
            int pos = get_line_pos(row, col);
            line[row] = square_get_number(&board->square[pos]);
        }
        if (!line_is_correct(line)) {
            return ERROR;
        }
    }
    return SUCCESS;
}

int board_verify_box(board_t* board) {
    square_t sqr_dup[NUM_SQUARES];
    sort_square_by_box(board, sqr_dup);

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

int get_square_values(char* numbers) {
    parser_t parser;
    parser_init(&parser, "board.txt");
    parser_process_file(&parser, numbers);
    parser_release(&parser);
    return SUCCESS;
}

int complete_squares(board_t* board, const char* numbers) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            int i = get_line_pos(row, col);
            square_init(&board->square[i], numbers[i]);
            square_set_box(&board->square[i], row, col);
        }
    }
    return SUCCESS;
}

int complete_drawing(board_t* board, const char* numbers) {
    get_board_drawing(board->drawing);
    int pos_cur_nbr = 0;
    for (int i = 0; i < 722; i++) {
        if (board->drawing[i] == 'X') {
            board->drawing[i] = square_get_number(&board->square[pos_cur_nbr]);
            board->pos_nbr[pos_cur_nbr] = i;
            pos_cur_nbr++;
        }
    }
    return SUCCESS;
}

int board_init(board_t* board) {
    char numbers[NUM_SQUARES];
    memset(numbers, 0, 81 * sizeof(char));
    memset(board->drawing, 0, 722 * sizeof(char));
    memset(board->pos_nbr, 0, 81 * sizeof(int));

    get_square_values(numbers);

    complete_squares(board, numbers);
    complete_drawing(board, numbers);
    return SUCCESS;
}
