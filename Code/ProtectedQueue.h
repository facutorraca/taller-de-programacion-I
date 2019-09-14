#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "Block.h"
#include <queue>
#include <mutex>
#include <condition_variable>

class ProtectedQueue {

    size_t max_q_len;
    std::queue<Block*> queue;
    std::condition_variable cv;
    std::mutex q_mtx;

    public:

        ProtectedQueue(size_t max_q_len);

        void wait();

        bool push(Block* block);

        bool empty();

        Block* pop();

        ~ProtectedQueue();

};

#endif
