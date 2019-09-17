#ifndef _BLOCK_BUFFER_H_
#define _BLOCK_BUFFER_H_

#include "Block.h"
#include <cstdint>
#include <vector>
#include <cstdbool>
#include <iostream>

#define DW_BYTES 4

class BlockBuffer {

    std::vector<uint32_t> buffer;
    size_t buff_len;

    private:

        void complete_buffer();

    public:

        BlockBuffer(size_t block_len);

        int numbers_stored();

        void add_number(const char* str_number);

        bool is_full();

        Block* create_compressed_block();

        ~BlockBuffer();

};


#endif

//        BlockBuffer(BlockBuffer&& block_buffer);
