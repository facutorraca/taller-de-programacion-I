#ifndef _COMPRESSOR_H_
#define _COMPRESSOR_H_

#include "ThreadCompressor.h"
#include <fstream>
#include <vector>

#include <iostream>

class Compressor {

    std::vector<ThreadCompressor> threads;
    std::ifstream i_file;
    std::ofstream o_file;

    size_t max_q_len;
    int num_thrds;
    int block_len;

    private:

        uint32_t find_minimal_bits(uint32_t number);

        void set_file_to_threads();

        void init_threads();

    public:

        Compressor(int num_thrds, size_t max_q_len, int block_len);

        void set_input_file(const char* i_filename);

        void set_output_file(const char* o_filename);

        void compress();

        ~Compressor();

};

#endif
