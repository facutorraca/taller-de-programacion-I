#ifndef _THREAD_ACCEPTOR_H_
#define _THREAD_ACCEPTOR_H_

#include "server_Thread.h"
#include "server_ThreadClient.h"
#include "server_ProtectedSet.h"
#include "server_SocketAcceptor.h"
#include <cstdbool>
#include <string>
#include <vector>
#include <atomic>
#include <map>

class ThreadAcceptor : public Thread {
    SocketAcceptor acceptor;
    ProtectedSet& directories;
    std::vector<ThreadClient*>& clients;
    std::map<std::string, std::string>& config;

    std::atomic<bool> server_running;

    private:
        void verify_clients();

        void run();

    public:
        ThreadAcceptor(const std::string port,
                       std::map<std::string, std::string>& config,
                       ProtectedSet& directories,
                       std::vector<ThreadClient*>& clients);

        void stop();

        ~ThreadAcceptor();
};

#endif
