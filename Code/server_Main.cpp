#include "server_Server.h"
#include "server_FileError.h"
#include "server_SocketAcceptorError.h"
#include "server_ThreadClient.h"
#include <string>
#include <iostream>

#define ERROR 1
#define SUCCESS 0
#define ARGS_EXPECTED 2

int main(int argc, char const *argv[]) {
    if (argc != ARGS_EXPECTED) {
        std::cerr << "2" << " arguments expected, "
                  << argc << " were given" << '\n';
    }

    std::string port(argv[1]);
    std::string file(argv[2]);

    try {
        Server server(port, file);
        server.start();
    } catch(const SocketAcceptorError &exception) {
        std::cerr << exception.what() << '\n';
    } catch(const FileError &exception) {
        std::cerr << exception.what() << '\n';
    }

    return SUCCESS;
}
