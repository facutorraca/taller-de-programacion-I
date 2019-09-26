#include "client_Input.h"
#include "client_Client.h"
#include "client_Instruction.h"
#include <iostream>
#include <vector>

#define ERROR 1
#define SUCCESS 0

int main(int argc, char const *argv[]) {
    std::string host(argv[1]);
    std::string port(argv[2]);

    Client client(host, port);
    client.run();

    return SUCCESS;
}
