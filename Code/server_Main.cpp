#include "common_socket.h"
#include "server_acceptor_socket.h"
#include <string>
#include <iostream>
#include <vector>

int main(int argc, char const *argv[]) {
    std::string port(argv[1]);

    AcceptorSocket acceptor_socket;
    acceptor_socket.bind(port);
    acceptor_socket.listen();
    Socket s_socket = acceptor_socket.accept();

    std::vector<char> buf;
    while (true) {
        s_socket.receive(buf);
        buf.clear();
    }

    return 0;
}
