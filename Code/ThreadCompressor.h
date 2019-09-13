#ifndef _THREAD_COMPRESSOR_H_
#define _THREAD_COMPRESSOR_H_

#include "ProtectedQueue.h"
#include "BlockBuffer.h"
#include <cstdint>
#include <fstream>
#include <thread>

class ThreadCompressor {

    std::ifstream* i_file;
    std::thread thread;
    ProtectedQueue* queue;
    BlockBuffer buffer;
    std::mutex& mtx;
    int blocks_len;
    int curr_block;

    private:

        void read_block();

        void compress();

    public:

        ThreadCompressor(int blocks_len, int start, std::mutex& mtx);

        void set_file(std::ifstream* i_file);

        void set_queue(ProtectedQueue* queue);

        void run();

        ~ThreadCompressor();
};

#endif
