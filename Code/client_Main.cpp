#include "client_Client.h"
#include "common_SocketError.h"
#include <iostream>
#include <string>
#include <vector>

#define ERROR 1
#define SUCCESS 0
#define ARGS_EXPECTED 2

int main(int argc, char const *argv[]) {
    if (argc != ARGS_EXPECTED) {
        std::cerr << "2" << " arguments expected, "
                  << argc << " were given" << '\n';
    }

    std::string host(argv[1]);
    std::string port(argv[2]);

    try {
        Client client(host, port);
        client.start();
    } catch(const SocketError& exception) {
        std::cerr << exception.what() << '\n';
    }

    return SUCCESS;
}
