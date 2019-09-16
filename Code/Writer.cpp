#include "Writer.h"
#include <fstream>
#include <iostream>
#include <cstdint>
#include <arpa/inet.h>

#define ERROR 1
#define SUCCESS 0
#define BINARY +2

/*--------------Public--------------*/
Writer::Writer() {

}

int Writer::set_file(const char* filename) {
    this->file.open(filename, std::ios::binary);
    if (this->file.is_open()) {
        return SUCCESS;
    }
    return ERROR;
}

void Writer::write_reference(uint32_t reference) {
    uint32_t ref_be = htonl(reference);
    file.write((char*)&ref_be, sizeof(uint32_t));
}

void Writer::write_bits(uint8_t bits) {
    file.write((char*)&bits, sizeof(uint8_t));
}

void Writer::write_number(const char* number_by_bit) {
    uint8_t number = this->get_byte_to_print(number_by_bit);
    file.write((char*)&number, sizeof(uint8_t));
}

/*--------------Private-------------*/
uint8_t Writer::get_byte_to_print(const char* number_by_bit) {
    uint8_t number = strtoul(number_by_bit, nullptr, BINARY);
    return number;
}

Writer::~Writer() {
    if (this->file.is_open()) {
        std::cout << "Input File Closed" << '\n';
        this->file.close();
    }
}
