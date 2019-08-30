#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "sudoku.h"

#define ERROR 1
#define SUCCESS 0

int main(int argc, char const *argv[]) {
    if (argc == 1) {
        printf("Modo no especificado\n");
        return ERROR;
    }
    
    if (strcmp("server", argv[1]) == 0) {
        return sudoku_init_as_server(argc, argv);
    }
    if (strcmp("client", argv[1]) == 0) {
        return sudoku_init_as_client(argc, argv);
    }

    printf("Modo no soportado, el primer parámetro debe ser server o client\n");
    return ERROR;
}
