#include "common_Socket.h"
#include "client_Client.h"
#include <cstring>
#include <iostream>
#include <vector>

int main(int argc, char const *argv[]) {
    std::string host(argv[1]);
    std::string port(argv[2]);

    Client client(host, port);
    client.connect();

    std::string input;
    while (true) {
        std::getline(std::cin, input);
        input.push_back('\n');

        client.send(input);
        input.erase(input.begin(), input.end());
    }

    return 0;
}
