#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "Block.h"
#include <queue>
#include <mutex>

class ProtectedQueue {

    size_t max_q_len;
    std::queue<Block> queue;
    //std::mutex& mtx;
    //std::condition_variable cond_var;

    public:

        ProtectedQueue(size_t max_q_len);

        bool push(Block block);

        Block pop();

        ~ProtectedQueue();

};

#endif
