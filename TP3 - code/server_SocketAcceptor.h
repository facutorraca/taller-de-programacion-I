#ifndef _SERVER_SOCKET_H_
#define _SERVER_SOCKET_H_

#include "common_Socket.h"
#include <string>
#include <sys/types.h>
#include <sys/socket.h>

class SocketAcceptor {
    int fd;

    public:
        SocketAcceptor();

        void bind(const std::string port);

        void listen();

        void close();

        Socket accept();

        ~SocketAcceptor();
};

#endif
