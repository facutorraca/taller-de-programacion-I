#ifndef _THREAD_CLIENT_H_
#define _THREAD_CLIENT_H_

#include "server_User.h"
#include "server_ClientProxy.h"
#include <thread>
#include <cstdbool>

class ThreadClient {
    User user;
    bool dead;

    ClientProxy client;
    std::thread thread;

    private:
        void communicate();

    public:
        ThreadClient(Socket socket);

        void run();

        ~ThreadClient();
};

#endif
