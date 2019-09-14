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
    this->queue = NULL;
    this->i_file = NULL;
    this->blocks_len = blocks_len;
    this->curr_block = start;
}

void CompressorThread::run() {
    this->thread = std::thread(&CompressorThread::compress, this);
}

void CompressorThread::join() {
    this->thread.join();
}

void CompressorThread::set_file(std::ifstream* i_file) {
    this->i_file = i_file;
}

void CompressorThread::set_queue(ProtectedQueue* queue) {
    this->queue = queue;
}

/*-------------Private--------------*/
void CompressorThread::compress() {
    //Valido unico thread
    while (!this->i_file->eof()) {
        this->read_block();
    }
}

void CompressorThread::read_block() {
    int nums_read = 0;
    char number[DW_BYTES];
    while (this->i_file->read(number, DW_BYTES) && nums_read < this->blocks_len) {
        this->buffer.add_number(number);
        nums_read++;
    }
    this->queue->push(this->buffer.create_compressed_block());
}

CompressorThread::~CompressorThread() {
    //Dont do anything
}
