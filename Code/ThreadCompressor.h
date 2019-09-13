#ifndef _THREAD_COMPRESSOR_H_
#define _THREAD_COMPRESSOR_H_

#include "ProtectedQueue.h"
#include "BlockBuffer.h"
#include <cstdint>
#include <fstream>

class ThreadCompressor {

    std::ifstream* i_file;
    BlockBuffer buffer;
    ProtectedQueue queue;
    int blocks_len;
    int curr_block;

    private:

        void read_block();

    public:

        ThreadCompressor(int blocks_len, int start, size_t max_q_len);

        void set_file(std::ifstream* file);

        void compress();

        ~ThreadCompressor();
};

#endif
