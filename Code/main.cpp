#include "Compressor.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sstream>

#define ERROR 1
#define SUCCESS 0
#define NO_FILE "-"

int main(int argc, char *argv[]) {
    if (arg != 5) {
        std::cerr << "Parametros invalidos" << '\n';
        return ERROR;
    }

    //argv[1] -> block_len
    //argv[2] -> num_thrds
    //argv[3] -> max_q_len
    //argv[4] -> i_filename
    //argv[5] -> o_filename

    Compressor compressor(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));

    if (strncmp(NO_FILE, argv[4], 1) != 0) {
        if (compressor.set_input_file(i_filename) == ERROR) {
            std::cerr << "El archivo no se pudo abrir o no existe" << '\n';
            return ERROR;
        };

    }
    if (strncmp(NO_FILE, argv[5], 1) != 0) {
        if (compressor.set_output_file(o_filename) == ERROR) {
            std::cerr << "El archivo no se pudo crear" << '\n';
            return ERROR;
        };
    }

    compressor.compress();
    return SUCCESS;
}
