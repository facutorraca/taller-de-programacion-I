#include "Reader.h"
#include "BlockBuffer.h"
#include <mutex>
#include <fstream>
#include <cstdint>
#include <cstring>


#define ERROR 1
#define SUCCESS 0

Reader::Reader(int block_len) {
    this->block_len = block_len;
}

int Reader::set_file(const char* filename) {
    this->file.open(filename, std::ios::binary);
    if (this->file.is_open()) {
        return SUCCESS;
    }
    return ERROR;
}


int Reader::set_and_read_block(int block_pos, BlockBuffer& buffer) {
    std::unique_lock<std::mutex> lock(this->f_mtx);
    if (this->set_block(block_pos) == ERROR) {
        return 0;
    }
    return this->read_block(buffer);
}

int Reader::set_block(int block_pos) {
    int pos = block_pos * this->block_len * sizeof(uint32_t);
    if(this->file.seekg(pos, std::ios_base::beg)) {
        return SUCCESS;
    }
    this->file.clear();
    return ERROR;
}

int Reader::read_block(BlockBuffer& buffer) {;
    char number[DW_BYTES];
    memset(number, 0, DW_BYTES * sizeof(char));

    while (!buffer.is_full() && this->file.read(number, DW_BYTES)) {
        buffer.add_number(number);
    }
    if (this->file.eof() || this->file.fail()) {
        this->file.clear();
    }

    return buffer.numbers_stored();
}

Reader::~Reader() {
    if (this->file.is_open()) {
        std::cout << "Output File Closed" << '\n';
        this->file.close();
    }
}
