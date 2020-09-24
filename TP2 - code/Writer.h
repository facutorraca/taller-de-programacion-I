#ifndef _WRITER_H_
#define _WRITER_H_

#include <fstream>
#include <cstdint>

class Writer {
    std::ostream* output; //Current output
    std::ofstream file;

    private:
        uint8_t get_byte_to_print(const char* number_by_bit);

    public:
        Writer();

        int set_file(const char* filename);

        void write_bits(uint8_t bits);

        void write_reference(uint32_t reference);

        void write_number(const char* number_by_bit);

        ~Writer();
};

#endif
