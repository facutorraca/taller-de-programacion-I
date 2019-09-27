#ifndef _PROTECTED_SET_H_
#define _PROTECTED_SET_H_

#include <set>
#include <string>
#include <cstdbool>

class ProtectedSet {

    std::set<std::string> set;

    public:
        bool find(std::string str);

        bool erase (std::string str);

        bool insert(std::string str);
};

#endif
