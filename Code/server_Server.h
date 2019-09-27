#ifndef _SERVER_H_
#define _SERVER_H_

#include "server_ProtectedSet.h"
#include "server_ThreadAcceptor.h"
#include <map>
#include <string>
#include <fstream>
#include <cstdbool>

class Server {
    ProtectedSet shared_files;
    ThreadAcceptor* acceptor;
    std::map<std::string, std::string> config;


    private:
        void control_quit();

        void load_configs(const std::string filename);

    public:
        Server(const std::string port, const std::string filename);

        void start();

        ~Server();
};

#endif
