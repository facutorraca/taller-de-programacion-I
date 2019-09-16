#ifndef _WRITER_H_
#define _WRITER_H_

#include <fstream>
#include <cstdint>

class Writer {

    std::ofstream file;

    private:

        uint8_t get_byte_to_print(const char* number_by_bit);

    public:

        Writer();

        void write_reference(uint32_t reference);

        void writer_bits(uint8_t bits);

        void write_number(const char* number_by_bit);

        int set_file(const char* filename);

        ~Writer();

};

#endif
