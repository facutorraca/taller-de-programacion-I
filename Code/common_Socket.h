#ifndef _SOCKET_H_
#define _SOCKET_H_

#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <vector>

class Socket {
    int fd;

    public:

        Socket();

        Socket(int fd);

        Socket(Socket&& other);

        int receive(std::string& buf);

        int send(const std::string& msg);

        int connect(const std::string host, const std::string port);

        ~Socket();
};

#endif
