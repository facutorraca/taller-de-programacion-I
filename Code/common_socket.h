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

        Socket(Socket &&other);

        int receive(std::vector<char>& buf);

        int send(const std::vector<char>& msg);

        int connect(const std::string port, const std::string host);

        ~Socket();
};

#endif
