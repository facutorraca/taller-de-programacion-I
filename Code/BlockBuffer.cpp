#include "BlockBuffer.h"
#include "Block.h"
#include <cstdint>
#include <iostream>
#include <cstring>
#include <arpa/inet.h>

/*--------------Public--------------*/
BlockBuffer::BlockBuffer(int block_len) {
    this->buffer = new uint32_t[block_len];
    this->buff_len = block_len;
    this->clear(); //Clear the buffer
}

void BlockBuffer::add_number(char* str_number) {
    uint32_t number;
    memcpy(&number, str_number, 4);

    this->buffer[this->curr_pos] = ntohl(number);
    this->curr_pos++;
}

Block BlockBuffer::create_compressed_block() {
    Block block(buffer, this->buff_len);
    block.compress();
    this->clear(); //Restart the buffer
    return block;
}

/*--------------Private--------------*/
void BlockBuffer::clear() {
    memset(this->buffer, 0, this->buff_len * sizeof(uint32_t));
    this->curr_pos = 0;
}

BlockBuffer::~BlockBuffer() {
    delete [] buffer;
}
