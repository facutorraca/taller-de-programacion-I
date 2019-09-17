#include "Compressor.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sstream>

#define SUCCESS 0
#define NO_FILE "-"

int main (int argc, char *argv[]) {
    int block_len = atoi(argv[1]);
    int num_thrds = atoi(argv[2]);
    int max_q_len = atol(argv[3]);

    const char* i_filename = argv[4];
    const char* o_filename = argv[5];

    Compressor compressor(num_thrds, max_q_len, block_len);

    if (strncmp(NO_FILE, i_filename, 1) != 0) {
        compressor.set_input_file(i_filename);
    }
    if (strncmp(NO_FILE, o_filename, 1) != 0) {
        compressor.set_output_file(o_filename);
    }

    compressor.compress();
    return SUCCESS;
}
