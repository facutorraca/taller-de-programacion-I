#include "common_Socket.h"
#include "server_AcceptorSocket.h"
#include <string>
#include <iostream>
#include <vector>

int main(int argc, char const *argv[]) {
    std::string port(argv[1]);

    AcceptorSocket acceptor_socket;
    acceptor_socket.bind(port);
    acceptor_socket.listen();
    Socket s_socket = acceptor_socket.accept();

    std::string buf;
    while (true) {
        s_socket.receive(buf);
        std::cout << buf;
        buf.erase(buf.begin(),buf.end());
    }

    return 0;
}
