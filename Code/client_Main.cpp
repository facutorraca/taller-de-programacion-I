#include "common_socket.h"
#include <cstring>
#include <iostream>
#include <vector>

int main(int argc, char const *argv[]) {
    std::string host(argv[1]);
    std::string port(argv[2]);

    Socket c_socket;
    c_socket.connect(port, host);

    std::string input;
    std::vector<char> msg;

    while (true) {
        msg.clear();
        std::getline(std::cin, input);

        msg.assign(input.begin(), input.end());
        msg.push_back('\n');

        c_socket.send(msg);
    }

    return 0;
}
