#ifndef _COMPRESSOR_H_
#define _COMPRESSOR_H_

#include "Collector.h"
#include <fstream>
#include <vector>

#include <iostream>

class Compressor {

    std::vector<Collector> collectors;
    std::ifstream i_file;
    std::ofstream o_file;

    private:

        uint32_t find_minimal_bits(uint32_t number);

        void init_collectors(int threads, int blk_len);

        void process_block(uint32_t min);

    public:

        Compressor(const char* i_filename, const char* o_filename, int threads, int blk_len) {
            this->i_file.open(i_filename, std::ios::binary);
            this->o_file.open(o_filename, std::ios::binary);
            this->init_collectors(threads, blk_len);
        }

        void compress();

        ~Compressor() {
            collectors.clear(); //NOSE SI ESTA BIEN!
            i_file.close();
            o_file.close();
        }

};

#endif
