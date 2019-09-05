#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "verifier.h"
#include "sudoku_server.h"
#include "sudoku_client.h"
//#include "verifier.h"

#define SUCCESS 0
#define ERROR 1

int main(int argc, char const *argv[]) {
    if (argc == 1) {
        printf("Modo no especificado\n");
        return ERROR;
    }

    if (strcmp("server", argv[1]) == 0) {
        if(verify_server_parameters(argc,argv)) {
            return sudoku_server_start(argv[2]);
        }
    }
    if (strcmp("client", argv[1]) == 0) {
        if(verify_client_parameters(argc,argv)) {
            return sudoku_client_start(argv[2], argv[3]);
        }
    }
    printf("Error en los parametros\n");
    return ERROR;
}
