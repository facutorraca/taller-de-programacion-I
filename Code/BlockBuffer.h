#ifndef _BLOCK_BUFFER_H_
#define _BLOCK_BUFFER_H_

#include <cstdint>
#include <iostream>
#include "Block.h"

#define DW_BYTES 4

class BlockBuffer {

    uint32_t* buffer;
    int buff_len;
    int curr_pos;

    private:

        void clear();

        uint32_t find_max();

        uint32_t find_min();

        uint8_t get_bits(uint32_t number);

        void subtract_reference(uint32_t ref);

    public:

        BlockBuffer(int block_len);

        void add_number(char* str_number);

        Block compress_block();

        ~BlockBuffer();

};


#endif
