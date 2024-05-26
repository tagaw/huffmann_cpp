#include <iostream>
#include "buffer.h"

// @brief sets ith bit in array
void set_i_bit(uint8_t* bit_array, int i) {
    bit_array[i/8] |= (uint8_t)1 << (i % 8);
    return;
}

// @brief clears ith bit in array
void clr_i_bit(uint8_t* bit_array, int i) {
    bit_array[i/8] &= ~((uint8_t)1 << (i % 8));
    return;
}

HuffmanBuffer::HuffmanBuffer(std::streambuf* buffer, HuffmanAlgorithm* hfa): buffer(buffer) {
    huffman = hfa;

    in_buffer = new uint8_t[BLOCK];
    out_buffer = new uint8_t[BLOCK];
    code_bits = new uint8_t[BLOCK];

    char* _tempcast = (char*)in_buffer;
    char* _tempcast2 = (char*)out_buffer;

    setg(0,0,0);
    setp(_tempcast2,_tempcast2+BLOCK);

    bit_idx = 0;
}

HuffmanBuffer::~HuffmanBuffer() {
    delete[] in_buffer;
    delete[] out_buffer;
    delete[] code_bits;
}

void HuffmanBuffer::compress(int bytes_in) {
    Code* table = huffman->get_table();
    for (int i = 0; i < bytes_in; i++) {
        int symb = in_buffer[i];
        Code c = table[symb];

        for (int j = 0; j < c.size(); j++) {
            if (bit_idx >= max_bit)  {
                buffer->sputn((char*)code_bits,BLOCK);
                bit_idx = 0;
            }
            if (c.get_bit(i)) {
                set_i_bit(code_bits,bit_idx);
            }
            else {
                clr_i_bit(code_bits,bit_idx);
            }
            bit_idx += 1;
        }
    }
}

void HuffmanBuffer::finish_code() {
    if (bit_idx < max_bit) {
        for (int i = bit_idx % 8; i > 0; i = (i+1)%8 ) {
            clr_i_bit(code_bits,bit_idx);
            bit_idx += 1;
        }
    }
    buffer->sputn((char*)code_bits,(bit_idx/8));
}

std::streambuf::int_type HuffmanBuffer::overflow(int c = EOF) {
    int wrote = pptr() - pbase();
    if (wrote > 0) {
        this->compress(wrote);
    }
    setp((char*)out_buffer,(char*)out_buffer+BLOCK);
    if (!traits_type::eq_int_type(c,traits_type::eof())) {
        sputc(c);
    }
    return traits_type::not_eof(c);
}

std::streambuf::int_type HuffmanBuffer::sync() {
    int res = this->overflow(traits_type::eof());
    this->finish_code();
    buffer->pubsync();
    return traits_type::eq_int_type(res, traits_type::eof()) ? -1 : 0;
}
