#include "BlockBuffer.h"
#include "Block.h"
#include <cstdint>
#include <iostream>
#include <cstring>
#include <cmath>
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

Block BlockBuffer::compress_block() {
    uint32_t ref = this->find_min();
    this->subtract_reference(ref);

    uint32_t max = this->find_max();
    uint8_t bits = this->get_bits(max);
    this->clear(); //Restart the buffer
    return Block(ref, bits);
}

/*--------------Private--------------*/

void BlockBuffer::clear() {
    memset(this->buffer, 0, this->buff_len * sizeof(uint32_t));
    this->curr_pos = 0;
}

uint32_t BlockBuffer::find_min() {
    uint32_t curr_min = this->buffer[0];
    for (int i = 1; i < this->buff_len; i++) {
        if (curr_min > this->buffer[i]) {
            curr_min = this->buffer[i];
        }
    }
    return curr_min;
}

uint32_t BlockBuffer::find_max() {
    uint32_t curr_max = this->buffer[0];
    for (int i = 1; i < this->buff_len; i++) {
        if (curr_max < this->buffer[i]) {
            curr_max = this->buffer[i];
        }
    }
    return curr_max;
}

void BlockBuffer::subtract_reference(uint32_t ref) {
    for (int i = 0; i < this->buff_len; i++) {
        this->buffer[i] = this->buffer[i] - ref;
    }
}

uint8_t BlockBuffer::get_bits(uint32_t number) {
    return (uint8_t)log2(number) + 1;
}

BlockBuffer::~BlockBuffer() {
    delete [] buffer;
}
