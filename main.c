#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "client.h"
#include "server.h"

#define ERROR 1
#define SUCCESS 0

int main(int argc, char const *argv[]) {
    if (argc == 1) {
        printf("Modo no especificado\n");
        return ERROR;
    }

    if (strcmp("server", argv[1]) == 0) {
        return server_init(argv[2]);
    }
    if (strcmp("client", argv[1]) == 0) {
        return client_init(argv[2], argv[3]);
    }

    printf("Modo no soportado, el primer parámetro debe ser server o client\n");
    return ERROR;
}
