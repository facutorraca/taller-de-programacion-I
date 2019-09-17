#include "BlockBuffer.h"
#include "Block.h"
#include <cstdint>
#include <cstdbool>
#include <iostream>
#include <cstring>
#include <arpa/inet.h>

/*--------------Public--------------*/
BlockBuffer::BlockBuffer(size_t block_len) {
    this->buff_len = block_len;
}

bool BlockBuffer::is_full() {
    return this->buffer.size() >= this->buff_len;
}

int BlockBuffer::numbers_stored() {
    return this->buffer.size();
}

void BlockBuffer::add_number(const char* str_number) {
    uint32_t number;
    memcpy(&number, str_number, 4);
    this->buffer.push_back(ntohl(number));
}

Block* BlockBuffer::create_compressed_block() {
    Block* block;
    if (this->buffer.size() == 1) { //Zero brick case
        block = new Block(buffer);
    } else {
        this->complete_buffer();
        block = new Block(buffer);
    }
    this->buffer.clear();
    block->compress();
    return block;
}

/*--------------Private--------------*/
void BlockBuffer::complete_buffer() {
    if (this->buffer.size() < this->buff_len) {
        int pos_last = this->buffer.size() - 1;
        while (this->buffer.size() < this->buff_len) {
            this->buffer.push_back(this->buffer[pos_last]);
        }
    }
}

BlockBuffer::~BlockBuffer() {}

/*BlockBuffer::BlockBuffer(BlockBuffer&& block_buffer) {
    this->buffer = block_buffer.buffer;
    this->buff_len = block_buffer.block_len;
    this->curr_pos = block_buffer.curr_pos;

    block_buffer.buffer = nullptr;
    block_buffer.block_len = 0;
    block_buffer.curr_pos = 0;
}*/
