#include "Compressor.h"
#include <iostream>
#include <sstream>

#define SUCCESS 0

//  int max_q_len = atoi(argv[2]);

int main (int argc, char *argv[]) {
    int block_len = atoi(argv[1]);
    int threads = atoi(argv[3]);

    char* i_filename = argv[4];
    char* o_filename = argv[5];

    Compressor compressor(i_filename, o_filename, threads, block_len);
    compressor.compress();

    return SUCCESS;
}
