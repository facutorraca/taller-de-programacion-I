#include "server_Server.h"
#include <string>
#include <iostream>

#define ERROR 1
#define SUCCESS 0

int main(int argc, char const *argv[]) {
    std::string port(argv[1]);

    Server server(port);
    server.start();

    return SUCCESS;
}
