#ifndef _SERVER_PROXY_H_
#define _SERVER_PROXY_H_

#include "common_Socket.h"
#include <string>

class ServerProxy {
    Socket socket;
    std::string host;
    std::string port;

    public:
        ServerProxy(const std::string host, const std::string port);

        void execute(const std::string cmd);

        void connect();

        ~ServerProxy();
};

#endif
