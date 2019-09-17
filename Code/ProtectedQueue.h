#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "Block.h"
#include <queue>
#include <mutex>
#include <cstdbool>
#include <condition_variable>

class ProtectedQueue {

    size_t max_q_len;
    std::queue<Block*> queue;
    std::condition_variable cv;
    std::mutex q_mtx;
    bool q_closed;

    int pushed;
    int poped;

    public:

        ProtectedQueue(size_t max_q_len);

        ProtectedQueue(ProtectedQueue&& p_queue);

        void push(Block* block);

        void wait();

        bool empty();

        void close();

        bool closed();

        Block* pop();

        int get_pop();

        int get_push();

        ProtectedQueue();

};

#endif
