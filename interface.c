#include <stdio.h>

#define SUCCESS 0
#define ERROR 1

int interface_get_new_instruction(char* buffer, int len_buf) {
    printf("Ingrese una isntruccion...\n");
    if(!fgets(buffer, len_buf, stdin)) {
        return ERROR;
    }
    return SUCCESS;
}
