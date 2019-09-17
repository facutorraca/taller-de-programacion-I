#include "WriterThread.h"
#include "ProtectedQueue.h"
#include "Block.h"
#include "Writer.h"
#include <condition_variable>
#include <fstream>
#include <cstdbool>
#include <iostream>

/*--------------Public--------------*/
WriterThread::WriterThread(std::vector<ProtectedQueue>& queues, Writer& writer):
    writer(writer),
    queues(queues) {}

void WriterThread::run() {
    this->thread = std::thread(&WriterThread::write_file, this);
}

void WriterThread::join() {
    this->thread.join();
}

/*--------------Private-------------*/
void WriterThread::write_file() {
    while (this->queues_are_open() || !this->queues_are_empty()) {
        for (size_t i = 0; i < queues.size(); i++) {
            if (!this->queues[i].empty()) {
                Block* block = this->queues[i].pop();
                block->print_in_file(this->writer);
            }
        }
    }

    std::cerr << "WriterThread finalized!" <<'\n';
    int sum_push = 0, sum_pop = 0;
    for (size_t i = 0; i < this->queues.size(); i++) {
        sum_pop = sum_pop + this->queues[i].get_pop();
        sum_push = sum_push + this->queues[i].get_push();
        std::cerr << "Thread" << i << " Number of Push: " << this->queues[i].get_push()
        << " Numbers of Pop's:" << this->queues[i].get_pop() << '\n';
    }
    std::cerr << "Total Push: " << sum_push <<" Total Pop: " << sum_pop <<"\n";
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
