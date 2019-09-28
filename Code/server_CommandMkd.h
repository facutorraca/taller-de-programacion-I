#ifndef _COMMAND_MKD_H_
#define _COMMAND_MKD_H_

#include "server_User.h"
#include "common_Socket.h"
#include "server_Command.h"
#include "server_ProtectedSet.h"
#include <string>
#include <map>

class CommandMkd : public Command {
    std::string answer;
    std::string directory;

    public:
        CommandMkd(std::string directory);

        void send_answer(Socket& socket);

        void execute(User& user,
                     std::map<std::string, std::string>& config,
                     ProtectedSet& directories);

        ~CommandMkd();
};

#endif
