#ifndef _COMPRESSOR_THREAD_H_
#define _COMPRESSOR_THREAD_H_

#include "ProtectedQueue.h"
#include "BlockBuffer.h"
#include <cstdint>
#include <fstream>
#include <thread>

class CompressorThread {

    std::ifstream* i_file;
    std::mutex& f_mtx;

    BlockBuffer buffer;
    int blocks_len;
    int curr_block;
    
    ProtectedQueue* queue;
    std::thread thread;

    private:

        void read_block();

        void compress();

    public:

        CompressorThread(int blocks_len, int start, std::mutex& f_mtx);

        void set_file(std::ifstream* i_file);

        void set_queue(ProtectedQueue* queue);

        void run();

        void join();

        ~CompressorThread();
};

#endif
