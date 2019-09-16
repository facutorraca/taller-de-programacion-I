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

        void complete_buffer();

    public:

        BlockBuffer(int block_len);

        void add_number(const char* str_number);

        Block* create_compressed_block();

        ~BlockBuffer();

};


#endif
