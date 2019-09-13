#include "ProtectedQueue.h"
#include "Block.h"
#include "Lock.h"
#include <cstdbool>
#include <iostream>

/*--------------Public--------------*/

ProtectedQueue::ProtectedQueue(size_t max_q_len) {
    this->max_q_len = max_q_len;
}

bool ProtectedQueue::push(Block block) {
    //Lock(this->mtx); //Lock for othr threads;
    if (this->queue.size() < this->max_q_len) {
        this->queue.push(block);
        return true;
    }
    return false;
}

Block ProtectedQueue::pop() {
    //Lock(this->mtx); //Lock for othr threads;
    Block block = this->queue.front();
    this->queue.pop();
    return block;
}

/*--------------Private--------------*/

ProtectedQueue::~ProtectedQueue() {}
