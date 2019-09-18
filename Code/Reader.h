#ifndef _READER_H_
#define _READER_H_

#include "BlockBuffer.h"
#include <mutex>
#include <fstream>

class Reader {

    std::istream* input; //Current input
    std::ifstream file;
    std::mutex f_mtx;
    size_t curr_pos;
    int block_len;

    private:

        int set_block(int block_pos);

        int read_block(BlockBuffer& buffer);


    public:

        Reader(int block_len);

        int set_file(const char* filename);

        int set_and_read_block(int block_pos, BlockBuffer& buffer);

        ~Reader();

};

#endif
