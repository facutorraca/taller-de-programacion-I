#include "Reader.h"
#include "BlockBuffer.h"
#include <mutex>
#include <fstream>
#include <cstdint>
#include <cstring>

#define ERROR 1
#define SUCCESS 0

/*--------------Public--------------*/
Reader::Reader(int block_len) {
    this->input = &std::cin; //Default
    this->block_len = block_len;
}

int Reader::set_file(const char* filename) {
    this->file.open(filename, std::ios::binary);
    if (this->file.is_open()) {
        this->input = &this->file;
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

/*--------------Private-------------*/
int Reader::set_block(int block_pos) {
    int pos = block_pos * this->block_len * sizeof(uint32_t);
    if(this->input->seekg(pos, std::ios_base::beg)) {
        return SUCCESS;
    }
    this->input->clear();
    return ERROR;
}

int Reader::read_block(BlockBuffer& buffer) {;
    char number[DW_BYTES];
    memset(number, 0, DW_BYTES * sizeof(char));

    while (!buffer.is_full() && this->input->read(number, DW_BYTES)) {
        buffer.add_number(number);
    }
    if (this->input->eof() || this->input->fail()) {
        this->input->clear();
    }

    return buffer.numbers_stored();
}

Reader::~Reader() {
    if (this->file.is_open()) {
        this->file.close();
    }
}
