#ifndef _SQUARE_H_
#define _SQUARE_H_

#define SUCCESS 0
#define ERROR 1

typedef struct square {
    char number;
    bool fixed;
} square_t;

int square_init(square_t* square, char number);

int square_reset(square_t* square);

int square_put_number(square_t* square, char number);

char square_get_number(square_t* square);

#endif
