#ifndef _SERVER_SOCKET_H_
#define _SERVER_SOCKET_H_

#include "common_socket.h"
#include <string>
#include <sys/types.h>
#include <sys/socket.h>

class AcceptorSocket {
    int fd;

    public:
        AcceptorSocket();

        int bind(const std::string port);

        int listen();

        Socket accept();

        ~AcceptorSocket();
};

#endif
