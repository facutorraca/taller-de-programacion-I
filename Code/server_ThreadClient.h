#ifndef _THREAD_CLIENT_H_
#define _THREAD_CLIENT_H_

#include "server_User.h"
#include "server_Thread.h"
#include "server_ClientProxy.h"
#include "server_ProtectedSet.h"
#include <map>
#include <thread>
#include <atomic>
#include <cstdbool>

class ThreadClient : public Thread {
    ClientProxy client;

    std::atomic<bool> dead;

    User user;
    ProtectedSet& directories;
    std::map<std::string, std::string>& config;

    private:
        void run();

    public:
        ThreadClient(Socket socket,
                     std::map<std::string, std::string>& config,
                     ProtectedSet& directories);

        void stop();

        bool is_dead();

        ~ThreadClient();
};

#endif
