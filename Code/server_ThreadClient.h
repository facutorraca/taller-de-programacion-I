#ifndef _THREAD_CLIENT_H_
#define _THREAD_CLIENT_H_

#include "server_User.h"
#include "server_ClientProxy.h"
#include <thread>
#include <cstdbool>
#include <map>

class ThreadClient {
    User user;
    bool dead;

    ClientProxy client;
    std::thread thread;

    std::map<std::string, std::string>& config;
    
    private:
        void communicate();

    public:
        ThreadClient(Socket socket,
                     std::map<std::string, std::string>& config);

        void run();

        ~ThreadClient();
};

#endif
