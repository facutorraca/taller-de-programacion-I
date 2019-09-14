#include "ProtectedQueue.h"
#include "Block.h"
#include "Lock.h"
#include <cstdbool>
#include <iostream>
#include <mutex>

/*--------------Public--------------*/
ProtectedQueue::ProtectedQueue(size_t max_q_len) {
    this->max_q_len = max_q_len;
}

bool ProtectedQueue::push(Block* block) {
    std::unique_lock<std::mutex> lock(this->q_mtx);

    bool was_empty = this->queue.empty();
    if (this->queue.size() < this->max_q_len) {
        this->queue.push(block);
        if (was_empty) {
            this->cv.notify_all();
        }
        return true;
    }

    return false;
}

Block* ProtectedQueue::pop() {
    std::unique_lock<std::mutex> lock(this->q_mtx);

    Block* block = this->queue.front();
    this->queue.pop();

    return block;
}

bool ProtectedQueue::empty() {
    return this->queue.empty();
}

void ProtectedQueue::wait() {
    std::unique_lock<std::mutex> lock(this->q_mtx);
    while (this->queue.empty()) {
        this->cv.wait(lock);
    }
}

/*--------------Private--------------*/
ProtectedQueue::~ProtectedQueue() {}
