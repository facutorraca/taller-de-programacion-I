#ifndef _SQUARE_H_
#define _SQUARE_H_

#define SUCCESS 0
#define ERROR 1

typedef struct square {
    char number;
    bool fixed;
    int box;
} square_t;

int square_init(square_t* square, char number);

int square_reset(square_t* square);

int square_put_number(square_t* square, char number);

int square_set_box(square_t* square, int row, int col);

int square_get_box(square_t* square);

char square_get_number(square_t* square);

#endif
