#include "Compressor.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sstream>

#define ERROR 1
#define SUCCESS 0
#define NO_FILE "-"

int main(int argc, char *argv[]) {
    if (argc != 6) {
        std::cerr << "Parametros invalidos" << '\n';
        return ERROR;
    }

    char* end_1; char* end_2; char* end_3;
    int block_len = strtol(argv[1], &end_1, 10);
    int num_thrds = strtol(argv[2], &end_2, 10);
    int max_q_len = strtol(argv[3], &end_3, 10);

    if (*end_1 || *end_2 || *end_3) {
        std::cerr << "Los parametros numericos de entrada son invalidos" <<'\n';
    }

    Compressor compressor(num_thrds, max_q_len, block_len);

    if (strncmp(NO_FILE, argv[4], 1) != 0) {
        if (compressor.set_input_file(argv[4]) == ERROR) {
            std::cerr << "El archivo no se pudo abrir o no existe" << '\n';
            return ERROR;
        }
    }
    if (strncmp(NO_FILE, argv[5], 1) != 0) {
        if (compressor.set_output_file(argv[5]) == ERROR) {
            std::cerr << "El archivo no se pudo crear" << '\n';
            return ERROR;
        }
    }

    compressor.compress();
    return SUCCESS;
}
