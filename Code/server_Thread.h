#ifndef _THREAD_H_
#define _THREAD_H_

#include <thread>

class Thread {
    std::thread thread;

    public:
        Thread () {}

        void start() {
            thread = std::thread(&Thread::run, this);
        }

        void join() {
            thread.join();
        }

        virtual void run() = 0;

        virtual ~Thread() {}
};

#endif
