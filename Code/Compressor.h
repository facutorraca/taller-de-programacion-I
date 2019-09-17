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

    int num_thrds;

    Reader reader;
    Writer writer;

    WriterThread* wtr_thread;
    std::vector<ProtectedQueue> queues;
    std::vector<CompressorThread*> cmp_threads;

    private:

        void init_threads(int block_len);

        void init_queues(size_t max_q_len);

    public:

        Compressor(int num_thrds, size_t max_q_len, int block_len);

        void set_input_file(const char* i_filename);

        void set_output_file(const char* o_filename);

        void compress();

        ~Compressor();

};

#endif
