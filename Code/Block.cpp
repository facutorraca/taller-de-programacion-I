#include "Block.h"
#include "Bitset.h"
#include <cstdint>
#include <iostream>
#include <cmath>
#include <bitset>
#include <arpa/inet.h>

/*--------------Public--------------*/
Block::Block(const uint32_t* numbers, int elements) {
    this->numbers = new uint32_t[elements];
    for (int i = 0; i < elements; i++) {
        this->numbers[i] = numbers[i];
    }
    this->elements = elements;
    this->ref = 0;
    this->bits = 0;
}

/*
Block::Block(Block&& block)
   : bitset(block.bitset),
     bits(block.bits),
     ref(block.ref),
     elements(block.elements),
     numbers(block.numbers)
{
   //block.bitset.clear();
   block.bits = 0;
   block.ref = 0;
   block.elements = 0;
   block.numbers = NULL;
 }
*/

void Block::print_in_file(std::ofstream* o_file) {
    uint32_t ref_be = htonl(this->ref);
    o_file->write((char*)&ref_be, sizeof(uint32_t));
    o_file->write((char*)&this->bits, sizeof(uint8_t));
    this->bitset.print_in_file(o_file);
//    std::bitset<32> bitset;

    /*
    for (int i = 0; i < this->elements; i++) {
        bitset = this->numbers[i];
        for (int j = 0; j < this->bits; j++) {
            if(bitset[this->bits - 1 - j]) std::cout << "1";
            else std::cout << "0";
        }
        std::cout << " ";
    }*/
//    std::cout << '\n';
}

void Block::compress() {
    this->ref = this->find_min();
    this->subtract_reference();

    uint32_t max = this->find_max();
    this->bits = this->get_bits(max);

    this->bitset.set_size(this->bits * this->elements);

    this->numbers_to_bits();
}

/*--------------Private-------------*/
uint32_t Block::find_min() {
    uint32_t curr_min = this->numbers[0];
    for (int i = 1; i < this->elements; i++) {
        if (curr_min > this->numbers[i]) {
            curr_min = this->numbers[i];
        }
    }
    return curr_min;
}

uint32_t Block::find_max() {
    uint32_t curr_max = this->numbers[0];
    for (int i = 1; i < this->elements; i++) {
        if (curr_max < this->numbers[i]) {
            curr_max = this->numbers[i];
        }
    }
    return curr_max;
}

void Block::subtract_reference() {
    for (int i = 0; i < this->elements; i++) {
        this->numbers[i] = this->numbers[i] - this->ref;
    }
}

uint8_t Block::get_bits(uint32_t number) {
    return (uint8_t)log2(number) + 1;
}

void Block::numbers_to_bits() {
    std::bitset<32> bitset;

    for (int i = 0; i < this->elements; i++) {
        bitset = this->numbers[i];
        for (int j = 0; j < this->bits; j++) {
            this->bitset.push_bit(bitset[this->bits - 1 - j]);
        }
    }
}

Block::~Block() {
    delete [] numbers;
}
