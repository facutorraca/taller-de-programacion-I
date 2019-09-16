#include "CompressorThread.h"
#include "ProtectedQueue.h"
#include "BlockBuffer.h"
#include "Block.h"
#include "Reader.h"
#include <iostream>
#include <cstring>
#include <cstdint>
#include <mutex>

#define DW_BYTES 4
#define SUCCESS 0
#define ERROR 1

/*--------------Public--------------*/
CompressorThread::CompressorThread(int block_len, int start, int off_blocks, Reader& reader):
    buffer(block_len),
    reader(reader) {
    this->queue = NULL; //Queue is set before when created
    this->off_blocks = off_blocks;
    this->curr_block = start;
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
    while (this->reader.set_and_read_block(this->curr_block, this->buffer) > 0) {
        Block* block = this->buffer.create_compressed_block();
        this->queue->push(block);
        this->curr_block = this->curr_block + this->off_blocks;
    }
    std::cout << "CompressorThread finalized!" <<'\n';
    this->queue->close();
}

CompressorThread::~CompressorThread() {
    //Dont do anything
}
