#ifndef _COMPRESSOR_THREAD_H_
#define _COMPRESSOR_THREAD_H_

#include "ProtectedQueue.h"
#include "BlockBuffer.h"
#include "Reader.h"
#include <cstdint>
#include <thread>

class CompressorThread {
    BlockBuffer buffer;
    int curr_block;
    int off_blocks;

    Reader& reader;

    ProtectedQueue& queue;
    std::thread thread;

    private:
        void compress();

    public:
        CompressorThread(size_t block_len,
                         int start,
                         int off_block,
                         Reader& reader,
                         ProtectedQueue& queue);

        void run();

        void join();

        ~CompressorThread();
};

#endif
