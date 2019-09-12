#include "BlockBuffer.h"
#include <cstdint>
#include <iostream>
#include <cstring>
#include <arpa/inet.h>

void BlockBuffer::push_back(char* number_as_str) {
    uint32_t number;
    memcpy(&number, number_as_str, 4);

    this->buffer[this->curr_pos] = ntohl(number);
    this->curr_pos++;
}

uint32_t BlockBuffer::pop_back() {
    this->curr_pos--;
    return this->buffer[this->curr_pos];
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

void BlockBuffer::substract_from_element(uint32_t min) {
    for (int i = 0; i < this->buff_len; i++) {
        this->buffer[i] = this->buffer[i] - min;
    }
}

void BlockBuffer::clear() {
    memset(this->buffer, 0, this->buff_len * sizeof(uint32_t));
    this->curr_pos = 0;
}

void BlockBuffer::print() {
    for (int i = 0; i < this->buff_len; i++) {
        std::cout << this->buffer[i] << " ";
    }
    std::cout << '\n';
}
