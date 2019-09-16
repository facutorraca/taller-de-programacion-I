#include "CompressorThread.h"
#include "ProtectedQueue.h"
#include "BlockBuffer.h"
#include "Block.h"
#include <iostream>
#include <cstring>
#include <cstdint>
#include <mutex>

#define DW_BYTES 4

/*--------------Public--------------*/
CompressorThread::CompressorThread(int blocks_len, int start, int off_blocks, std::mutex& f_mtx): f_mtx(f_mtx), buffer(blocks_len) {
    this->queue = NULL; //Queue is set before when created
    this->i_file = NULL; //File is set before when created
    this->blocks_len = blocks_len;
    this->off_blocks = off_blocks;
    this->curr_block = start;
}

void CompressorThread::set_file(std::ifstream* i_file) {
    this->i_file = i_file;
}

void CompressorThread::set_queue(ProtectedQueue* queue) {
    this->queue = queue;
}

void CompressorThread::run() {
    this->thread = std::thread(&CompressorThread::compress, this);
}

void CompressorThread::join() {
    this->thread.join();
}

/*-------------Private--------------*/
void CompressorThread::compress() {
    while (this->read_block() > 0) {
        Block* block = this->buffer.create_compressed_block();
        this->queue->push(block);
    }
    std::cout << "CompressorThread finalized!" <<'\n';
    this->queue->close();
}

int CompressorThread::read_block() {
    char number[DW_BYTES];
    memset(number, 0, DW_BYTES * sizeof(char));

    std::unique_lock<std::mutex> lock(this->f_mtx);
    int nums_read = 0;

    int offset = this->curr_block * this->blocks_len * sizeof(uint32_t);
    if(this->i_file->seekg(offset, std::ios_base::beg)) {
        while (nums_read < this->blocks_len && this->i_file->read(number, DW_BYTES)) {
            this->buffer.add_number(number);
            nums_read++;
        }
    }
    this->curr_block = this->curr_block + this->off_blocks;
    this->i_file->clear();
    return nums_read;
}

CompressorThread::~CompressorThread() {
    //Dont do anything
}
