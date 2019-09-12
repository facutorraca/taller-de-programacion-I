#ifndef _COLLECTOR_H_
#define _COLLECTOR_H_

#include "BlockBuffer.h"
#include <cstdint>
#include <fstream>

class Collector {

    BlockBuffer buffer;
    std::ifstream* i_file;
    int block_len;

    public:

        Collector(std::ifstream* i_file, int block_len) : buffer(block_len) {
            this->block_len = block_len;
            this->i_file = i_file;
        }

        bool collect();

        void print();

        void clear();

        void substract_from_element(uint32_t min);

        uint32_t find_max();

        uint32_t find_min();

        ~Collector() {
            //SE elimina el buffer
        }
};

#endif
