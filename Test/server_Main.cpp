#include "server_Server.h"
#include <string>
#include <iostream>

int main(int argc, char const *argv[]) {
    std::string port(argv[1]);

    Server server(port);
    server.run();

    return 0;
}
