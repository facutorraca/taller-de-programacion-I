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
    this->clear(); //Init the buffer
}

void BlockBuffer::add_number(char* str_number) {
    uint32_t number;
    memcpy(&number, str_number, 4);
    std::cout << number << '\n';

    this->buffer[this->curr_pos] = ntohl(number);
    this->curr_pos++;
}

Block* BlockBuffer::create_compressed_block() {
    this->complete_buffer();
    //std::cout << this->buffer[0] << "  " << this->buffer[1] << "  "<< this->buffer[2] << "  "<<this->buffer[3] << "\n";
    Block* block = new Block(buffer, this->buff_len);
    this->clear(); //Restart the buffer
    block->compress();
    return block;
}

/*--------------Private--------------*/
void BlockBuffer::clear() {
    memset(this->buffer, 0, this->buff_len * sizeof(uint32_t));
    this->curr_pos = 0;
}

void BlockBuffer::complete_buffer() {
    if (this->curr_pos < this->buff_len) {
        int pos_last = this->curr_pos - 1;
        while (this->curr_pos < this->buff_len) {
            this->buffer[this->curr_pos] = this->buffer[pos_last];
            this->curr_pos++;
        }
    }
}

BlockBuffer::~BlockBuffer() {
    delete [] buffer;
}
