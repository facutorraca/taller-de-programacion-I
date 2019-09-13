#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "Block.h"
#include <mutex>
#include <queue>

class ProtectedQueue {

    size_t max_q_len;
    std::mutex q_mutex;
    std::queue<Block> queue;

    public:

        ProtectedQueue(size_t max_q_len);

        bool push(Block block);

        Block pop();

        ~ProtectedQueue();

};

#endif
