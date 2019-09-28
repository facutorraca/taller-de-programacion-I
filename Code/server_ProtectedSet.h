#ifndef _PROTECTED_SET_H_
#define _PROTECTED_SET_H_

#include <set>
#include <mutex>
#include <string>
#include <vector>
#include <cstdbool>

class ProtectedSet {

    std::mutex s_mtx;
    std::set<std::string> set;

    public:
        bool erase (std::string str);

        bool insert(std::string str);

        void get_elements(std::vector<std::string>& buf);
};

#endif
 
