#ifndef _COMMAND_QUIT_H_
#define _COMMAND_QUIT_H_

#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include "server_ProtectedSet.h"
#include <string>
#include <map>

class CommandQuit : public Command {
    std::string answer;

    public:
        CommandQuit();

        void send_answer(Socket& socket);

        void execute(User& user,
                     std::map<std::string, std::string>& config,
                     ProtectedSet& directories);

        ~CommandQuit();
};

#endif
