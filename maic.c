#include <stdio.h>
#include <stdlib.h>

#define ERROR -1
#define SUCCESS 0

int main(int argc, char const *argv[]) {
    if (argc == 1) {
        fprintf(stderr, "Modo no especificado\n");
        return ERROR;
    }

    const char* mode = argv[1];
    if (strcmp("client", mode) == 0) {
        //Do something with "client"
        return SUCCESS;
    }
    if (strcmp("server", mode) == 0) {
        //Do something with "server"
        return SUCCESS;
    }
    fprintf(stderr, "Modo no soportado, el primer parámetro debe ser server o client\n");
    return ERROR;
}
