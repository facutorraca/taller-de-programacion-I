#include "common_Socket.h"
#include <cstring>
#include <iostream>
#include <vector>

int main(int argc, char const *argv[]) {
    std::string host(argv[1]);
    std::string port(argv[2]);

    Socket c_socket;
    c_socket.connect(port, host);

    std::string input;

    while (true) {
        std::getline(std::cin, input);
        input.push_back('\n');

        c_socket.send(input);
        input.erase(input.begin(), input.end());
    }

    return 0;
}
