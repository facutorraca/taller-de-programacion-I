#include <stdio.h>
#include <stdlib.h>

#define ERROR 1
#define SUCCESS 0

int main(int argc, char const *argv[]) {
    if (argc == 1) {
        printf("Modo no especificado\n");
        return ERROR;
    }

    if (strcmp("server", argv[1]) == 0) {
        server_init(argv[2]);
        return SUCCESS;
    }
    if (strcmp("client", argv[1]) == 0) {
        client_init(argv[2], argv[3]);
        return SUCCESS;
    }

    printf("Modo no soportado, el primer parámetro debe ser server o client\n");
    return ERROR;
}
