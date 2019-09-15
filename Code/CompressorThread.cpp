#include "CompressorThread.h"
#include "ProtectedQueue.h"
#include "BlockBuffer.h"
#include "Block.h"
#include <iostream>
#include <cstring>
#include <cstdint>

#define DW_BYTES 4
//

/*--------------Public--------------*/
CompressorThread::CompressorThread(int blocks_len, int start, std::mutex& f_mtx): f_mtx(f_mtx), buffer(blocks_len) {
    this->queue = NULL; //Queue is set before when created
    this->i_file = NULL; //File is set before when created
    this->blocks_len = blocks_len;
    this->curr_block = start;
}

void CompressorThread::set_file(std::ifstream* i_file) {
    this->i_file = i_file;
}

void CompressorThread::set_queue(ProtectedQueue* queue) {
    this->queue = queue;
}

void CompressorThread::run() {
    //this->thread = std::thread(&CompressorThread::compress, this);
    this->compress();
}

void CompressorThread::join() {
    this->thread.join();
}

/*-------------Private--------------*/
void CompressorThread::compress() {
    //Valido unico thread
    while (!this->i_file->eof()) {
        this->read_block();
    }
    std::cout << "CompressorThread finalized!" <<'\n';
    this->queue->close();
}

void CompressorThread::read_block() {
    char number[DW_BYTES];
    memset(number, 0, DW_BYTES * sizeof(char));

    int nums_read = 0;
    while (nums_read < this->blocks_len && this->i_file->read(number, DW_BYTES)) {
        this->buffer.add_number(number);
        nums_read++;
    }
    if (!i_file->eof()) {
        Block* block = this->buffer.create_compressed_block();
        this->queue->push(block);
    }
}

CompressorThread::~CompressorThread() {
    //Dont do anything
}
