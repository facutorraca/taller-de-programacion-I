#ifndef _COMPRESSOR_H_
#define _COMPRESSOR_H_

#include "ThreadCompressor.h"
#include <fstream>
#include <vector>
#include <mutex>

#include <iostream>

class Compressor {

    std::vector<ThreadCompressor*> cmp_threads;
    std::vector<ProtectedQueue*> queues;
    std::ifstream i_file;
    std::ofstream o_file;
    std::mutex mtx;

    size_t max_q_len;
    int num_thrds;
    int block_len;

    private:

        uint32_t find_minimal_bits(uint32_t number);

        void set_file_to_threads();

        void init_threads();

        void init_queues();

    public:

        Compressor(int num_thrds, size_t max_q_len, int block_len);

        void set_input_file(const char* i_filename);

        void set_output_file(const char* o_filename);

        void compress();

        ~Compressor();

};

#endif
