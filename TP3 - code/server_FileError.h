#ifndef _FILE_ERROR_H_
#define _FILE_ERROR_H_

#include <stdexcept>

class FileError : public std::runtime_error {
    public:
        explicit FileError(const char* error) : runtime_error(error) {}
};

#endif
