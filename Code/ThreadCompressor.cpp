#include "ThreadCompressor.h"
#include "ProtectedQueue.h"
#include "BlockBuffer.h"
#include "Block.h"
#include <iostream>
#include <cstring>
#include <cstdint>

#define DW_BYTES 4
//

/*--------------Public--------------*/
ThreadCompressor::ThreadCompressor(int blocks_len, int start, std::mutex& mtx): buffer(blocks_len), mtx(mtx) {
    this->queue = NULL;
    this->i_file = NULL;
    this->blocks_len = blocks_len;
    this->curr_block = start;
}

void ThreadCompressor::run() {
    this->thread = std::thread(&ThreadCompressor::compress, this);
}

void ThreadCompressor::join() {
    this->thread.join();
}

void ThreadCompressor::set_file(std::ifstream* i_file) {
    this->i_file = i_file;
}

void ThreadCompressor::set_queue(ProtectedQueue* queue) {
    this->queue = queue;
}

/*-------------Private--------------*/
void ThreadCompressor::compress() {
    //this->i_file->seekg(this->curr_block, this->i_file->beg); //Set the correct position of first block
    while (!this->i_file->eof()) {
        this->read_block();
        //this->curr_block = this->curr_block + this->blocks_len;
        //this->i_file->seekg(this->curr_block, this->i_file->beg);
    }
}

void ThreadCompressor::read_block() {
    int nums_read = 0;

    char number[DW_BYTES];
    while (this->i_file->read(number, DW_BYTES) && nums_read < this->blocks_len) {
        this->buffer.add_number(number);
        nums_read++;
    }
    //std::cerr << "llegue" << '\n';
    Block cmp_block = this->buffer.compress_block();
    this->queue->push(cmp_block);
}

ThreadCompressor::~ThreadCompressor() {
    //Dont do anything
}
