#ifndef _BLOCK_BUFFER_H_
#define _BLOCK_BUFFER_H_

#include "Block.h"
#include <cstdint>
#include <vector>
#include <cstdbool>
#include <iostream>

#define DW_BYTES 4

class BlockBuffer {

    size_t block_len;
    std::vector<uint32_t> buffer;

    private:

        void complete_buffer();

    public:

        BlockBuffer(size_t block_len);

        bool is_full();

        int numbers_stored();

        Block* create_compressed_block();

        void add_number(const char* str_number);

        ~BlockBuffer();

};

#endif
