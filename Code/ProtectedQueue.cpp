#include "ProtectedQueue.h"
#include "Block.h"
#include <cstdbool>
#include <iostream>
#include <mutex>

/*--------------Public--------------*/
ProtectedQueue::ProtectedQueue(size_t max_q_len) {
    this->max_q_len = max_q_len;
    this->q_closed = false;
}

ProtectedQueue::ProtectedQueue(ProtectedQueue&& p_queue):
    queue(p_queue.queue)
{
    this->max_q_len = p_queue.max_q_len;
    this->q_closed = p_queue.q_closed;

    p_queue.max_q_len = 0;
    p_queue.q_closed = true;
}

void ProtectedQueue::push(Block* block) {
    std::unique_lock<std::mutex> lock(this->q_mtx);
    while (this->queue.size() >= this->max_q_len) {
        this->cv_push.wait(lock);
    }

    this->queue.push(block);
    this->cv_push.notify_all();
}

Block* ProtectedQueue::pop() {
    std::unique_lock<std::mutex> lock(this->q_mtx);
    while (this->queue.empty() && !this->q_closed) {
        this->cv_pop.wait(lock);
    }

    if (this->queue.empty()) {
        //The queue is not receiving more elements
        return nullptr;
    } else {
        Block* block = this->queue.front();
        this->queue.pop();
        this->cv_pop.notify_all();
        return block;
    }
}


bool ProtectedQueue::empty() {
    std::unique_lock<std::mutex> lock(this->q_mtx);
    return this->queue.empty();
}

void ProtectedQueue::close() {
    std::unique_lock<std::mutex> lock(this->q_mtx);
    this->q_closed = true;
    //Notify free pass to take!
    this->cv_pop.notify_all();
}

bool ProtectedQueue::closed() {
    std::unique_lock<std::mutex> lock(this->q_mtx);
    return this->q_closed;
}

/*--------------Private--------------*/
ProtectedQueue::~ProtectedQueue() {}
