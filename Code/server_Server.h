#ifndef _SERVER_H_
#define _SERVER_H_

#include "server_ProtectedSet.h"
#include "server_ThreadClient.h"
#include "server_ThreadAcceptor.h"
#include <map>
#include <string>
#include <vector>
#include <cstdbool>

class Server {
    ProtectedSet directories;
    ThreadAcceptor* acceptor;
    std::vector<ThreadClient*> clients;
    std::map<std::string, std::string> config;


    private:
        void wait_quit();

        void stop_clients(); 

        void load_configs(const std::string filename);

    public:
        Server(const std::string port, const std::string filename);

        void start();

        ~Server();
};

#endif
