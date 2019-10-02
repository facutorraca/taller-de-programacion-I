#include "BlockBuffer.h"
#include "Block.h"
#include <cstdint>
#include <cstdbool>
#include <iostream>
#include <cstring>
#include <arpa/inet.h>

/*--------------Public--------------*/
BlockBuffer::BlockBuffer(size_t block_len) {
    this->block_len = block_len;
}

bool BlockBuffer::is_full() {
    return this->buffer.size() >= this->block_len;
}

int BlockBuffer::numbers_stored() {
    return this->buffer.size();
}

void BlockBuffer::add_number(uint32_t number) {
    this->buffer.push_back(ntohl(number));
}

Block* BlockBuffer::create_compressed_block() {
    if (this->buffer.size() > 1) {
        //To avoid zero brick case
        this->complete_buffer();
    }
    Block*  block = new Block(buffer);
    this->buffer.clear();
    block->compress();
    return block;
}

/*--------------Private--------------*/
void BlockBuffer::complete_buffer() {
    if (this->buffer.size() < this->block_len) {
        int last_pos = this->buffer.size() - 1;
        while (this->buffer.size() < this->block_len) {
            this->buffer.push_back(this->buffer[last_pos]);
        }
    }
}

BlockBuffer::~BlockBuffer() {}
