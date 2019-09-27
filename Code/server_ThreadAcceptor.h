#ifndef _THREAD_ACCEPTOR_H_
#define _THREAD_ACCEPTOR_H_

#include "server_ThreadClient.h"
#include "server_SocketAcceptor.h"
#include <cstdbool>
#include <string>
#include <vector>
#include <map>

class ThreadAcceptor {
    std::thread thread;
    bool server_running;
    SocketAcceptor acceptor;
    std::vector<ThreadClient*> clients;
    std::map<std::string, std::string>& config;

    private:
        void verify_clients();

        void accept_clients();

    public:
        ThreadAcceptor(const std::string port,
                       std::map<std::string, std::string>& config);

        void run();

        ~ThreadAcceptor();
};

#endif
