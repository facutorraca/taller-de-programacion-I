#include "Collector.h"
#include <iostream>
#include <cstring>
#include <cstdint>

#define DW_BYTES 4

bool Collector::collect() {
    char number[DW_BYTES];

    int nums_read = 0;
    while (this->i_file->read(number, DW_BYTES) && nums_read < this->block_len) {
        this->buffer.push_back(number);
        nums_read++;
    }
    return !i_file->eof();
}

void Collector::substract_from_element(uint32_t min) {
    this->buffer.substract_from_element(min);
}

void Collector::print() {
    std::cout << "Collected: ";
    this->buffer.print();
    this->buffer.clear();
}

void Collector::clear() {
    this->buffer.clear();
}

uint32_t Collector::find_max() {
    return this->buffer.find_max();
}

uint32_t Collector::find_min() {
    return this->buffer.find_min();
}
