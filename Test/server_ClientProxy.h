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
        ClientProxy(Socket socket);

        Command* get_command();

        void send_welcome_message();

        void send_command_answer(Command* cmd);

        ~ClientProxy();
};

#endif
