#ifndef _COMPRESSOR_H_
#define _COMPRESSOR_H_

#include "CompressorThread.h"
#include "WriterThread.h"
#include <fstream>
#include <vector>
#include <mutex>
#include <iostream>

class Compressor {

    int num_thrds;

    std::ifstream i_file;
    std::ofstream o_file;
    std::mutex i_file_mtx;

    WriterThread* wtr_thread;
    std::vector<ProtectedQueue*> queues;
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
