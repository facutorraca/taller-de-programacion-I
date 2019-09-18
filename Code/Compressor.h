#ifndef _COMPRESSOR_H_
#define _COMPRESSOR_H_

#include "CompressorThread.h"
#include "WriterThread.h"
#include "Reader.h"
#include "Writer.h"
#include <vector>
#include <mutex>
#include <iostream>

class Compressor {
    Reader reader;
    Writer writer;

    WriterThread* wtr_thread;
    std::vector<ProtectedQueue> queues;
    std::vector<CompressorThread*> cmp_threads;

    private:
        void init_queues(size_t max_q_len, int num_thrds);

        void init_threads(size_t block_len, int num_thrds);

    public:
        explicit Compressor(int num_thrds, size_t max_q_len, size_t block_len);

        void set_input_file(const char* i_filename);

        void set_output_file(const char* o_filename);

        void compress();

        ~Compressor();
};

#endif
