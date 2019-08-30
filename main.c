#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "sudoku_server.h"
#include "sudoku_client.h"
#include "verifier.h"

#define SUCCESS 0
#define ERROR 1

int main(int argc, char const *argv[]) {
    if (argc == 1) {
        printf("Modo no especificado\n");
        return ERROR;
    }

    if (strcmp("server", argv[1]) == 0) {
        /*
        if(controller_validate_server_parameters(argc,argv) == ERROR) {
            return ERROR;
        }
        */
        return sudoku_server_start(argv[2]);
    }
    if (strcmp("client", argv[1]) == 0) {
        /*
        if(controller_validate_client_parameters(argc,argv) == ERROR) {
            return ERROR;
        }
        return sudoku_init_as_client(argv[2], argv[3]);
        */
        return SUCCESS;
    }

    printf("Modo no soportado, el primer parámetro debe ser server o client\n");
    return ERROR;
}
