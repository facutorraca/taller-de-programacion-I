#ifndef _CLIENT_PROXY_H_
#define _CLIENT_PROXY_H_

#include "common_Socket.h"
#include "server_Command.h"
#include "server_CommandFactory.h"
#include <string>

class ClientProxy {
    Socket socket;
    CommandFactory cmd_factory;

    private:
        void interpret_command(std::string cmd);

    public:
        explicit ClientProxy(Socket socket);

        void disconnect();

        Command* get_command();

        int send_welcome_message(std::string msg);

        int send_command_answer(Command* cmd);

        ~ClientProxy();
};

#endif
