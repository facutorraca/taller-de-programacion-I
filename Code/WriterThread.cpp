#include "WriterThread.h"
#include "ProtectedQueue.h"
#include "Block.h"
#include "Writer.h"
#include <vector>
#include <fstream>
#include <cstdbool>
#include <iostream>

/*--------------Public--------------*/
WriterThread::WriterThread(std::vector<ProtectedQueue>& queues,
                         Writer& writer):
                         writer(writer),
                         queues(queues) {}

void WriterThread::start() {
    this->thread = std::thread(&WriterThread::write_file, this);
}

void WriterThread::join() {
    this->thread.join();
}

/*--------------Private-------------*/
void WriterThread::write_file() {
    while (this->queues_are_open() || !this->queues_are_empty()) {
        for (size_t i = 0; i < queues.size(); i++) {
            Block* block = this->queues[i].pop();
            if (block) {
                block->print_in_file(this->writer);
                delete block;
            }
        }
    }
}

bool WriterThread::queues_are_open() {
    bool open = false;
    for (size_t i = 0; i < this->queues.size(); i++) {
        if (!this->queues[i].closed()) {
            open = true;
        }
    }
    return open;
}

bool WriterThread::queues_are_empty() {
    bool empty = true;
    for (size_t i = 0; i < this->queues.size(); i++) {
        if (!this->queues[i].empty()) {
            empty = false;
        }
    }
    return empty;
}

WriterThread::~WriterThread() {}
