#ifndef _BLOCK_BUFFER_H_
#define _BLOCK_BUFFER_H_

#include "Block.h"
#include <cstdint>
#include <cstdbool>
#include <iostream>

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

        int numbers_stored();

        void add_number(const char* str_number);

        bool is_full();

        Block* create_compressed_block();

        ~BlockBuffer();

};


#endif
