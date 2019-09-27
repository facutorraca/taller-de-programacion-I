#ifndef _THREAD_ACCEPTOR_H_
#define _THREAD_ACCEPTOR_H_

#include "server_ThreadClient.h"
#include "server_SocketAcceptor.h"
#include <cstdbool>
#include <string>
#include <vector>

class ThreadAcceptor {
    std::thread thread;
    bool server_running;
    SocketAcceptor acceptor;
    std::vector<ThreadClient*> clients;

    private:
        void verify_clients();

        void accept_clients();

    public:
        ThreadAcceptor(std::string port);

        void run();

        ~ThreadAcceptor();
};

#endif
