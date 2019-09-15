#include "ProtectedQueue.h"
#include "Block.h"
#include "Lock.h"
#include <cstdbool>
#include <iostream>
#include <mutex>

/*--------------Public--------------*/
ProtectedQueue::ProtectedQueue(size_t max_q_len) {
    this->max_q_len = max_q_len;
    this->q_closed = false;

    this->pushed = 0;
    this->poped = 0;
}

bool ProtectedQueue::push(Block* block) {
    std::unique_lock<std::mutex> lock(this->q_mtx);
    std::cout << "Mutex Compressor" << '\n';
    bool was_empty = this->queue.empty();
    if (this->queue.size() < this->max_q_len) {
        this->queue.push(block);
        this->pushed++;
        if (was_empty) {
            this->cv.notify_all();
        }
        return true;
    }
    return false;
}

Block* ProtectedQueue::pop() {
    std::unique_lock<std::mutex> lock(this->q_mtx);
    std::cout << "Mutex Writer" << '\n';
    while (this->queue.empty() && !this->q_closed) {
        this->cv.wait(lock);
    }

    Block* block = this->queue.front();
    this->queue.pop();
    this->poped++;

    return block;
}

bool ProtectedQueue::empty() {
    std::unique_lock<std::mutex> lock(this->q_mtx);
    return this->queue.empty();
}

void ProtectedQueue::close() {
    this->q_closed = true;
}

bool ProtectedQueue::closed() {
    return this->q_closed;
}

int ProtectedQueue::get_pop() {
    return this->poped;
}


int ProtectedQueue::get_push() {
    return this->pushed;
}

/*--------------Private--------------*/
ProtectedQueue::~ProtectedQueue() {}
