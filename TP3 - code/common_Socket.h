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

        explicit Socket(int fd);

        Socket(Socket&& other);

        void receive(std::string& buf);

        void send(const std::string& msg);

        void connect(const std::string host, const std::string port);

        void close();

        ~Socket();
};

#endif
