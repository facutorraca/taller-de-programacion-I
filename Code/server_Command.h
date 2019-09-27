#ifndef _COMMAND_H_
#define _COMMAND_H_

#include "server_User.h"
#include "common_Socket.h"
#include <string>
#include <map>

class Command {
    public:
        virtual void execute(User& user,
                             std::map<std::string, std::string>& config) = 0;

        virtual void send_answer(Socket& socket) = 0;

        virtual ~Command() {} //Esto esta mal!!
};

#endif
