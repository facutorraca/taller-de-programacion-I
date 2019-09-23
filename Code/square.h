#ifndef _SQUARE_H_
#define _SQUARE_H_

typedef struct square {
    char number;
    bool fixed;
    int box;
} square_t;

//Inicializa una instacia de square con el numero
//enviado por parametro
//PRE: self apunta un sector válido de memoria
int square_init(square_t* self, char number);

//Resetea la celdad a su estado inicial
//PRE: self fue inicializado previamente
int square_reset(square_t* self);

//Coloca un si es posible
//PRE: self fue inicializad previamente.
//Number pertenece al intervalo [1,9]
int square_put_number(square_t* self, char number);

//Define la caja en la que pertenece en el tablero
//PRE: self fue inicializado previamente
int square_set_box(square_t* self, int row, int col);

//Obtiene la caja en la que pertenece en el tablero
//PRE: self fue inicializado y su caja fue definida previamente
int square_get_box(square_t* self);

//Obtiene el numero.
//PRE: self fue inicializado previamente
char square_get_number(square_t* self);

//Destruye una instacia de square
//PRE: self fue inicializado previamente
int square_release(square_t* self);

#endif
