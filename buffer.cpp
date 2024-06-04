#include <iostream>
#include "buffer.h"


/*Local helper functions*/

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

/*PRIVATE FUNCTIONS*/

void HuffmanBuffer::compress(int bytes_in) {
    Code* table = huffman->get_table();
    for (int i = 0; i < bytes_in; i++) {
        int symb = out_buffer[i];
        Code c = table[symb];
    
        for (int j = 0; j < c.size(); j++) {
            if (bit_idx >= max_bit)  {
                buffer->sputn((char*)code_bits,BLOCK);
                bit_idx = 0;
            }
            if (c.get_bit(j)) {
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
        while (bit_idx % 8 > 0) {
            clr_i_bit(code_bits,bit_idx);
            bit_idx += 1;
        }
    }
    buffer->sputn((char*)code_bits,(bit_idx/8));
}


/*PROTECTED FUNCTIONS*/

// std::streambuf::int_type underflow() {

// }

std::streambuf::int_type HuffmanBuffer::overflow(int c) {
    int wrote = pptr() - pbase();

    if (wrote > 0) { // compresses buffer, gets flushed when code bits exceed BLOCK bytes
        compress(wrote);
    }
    setp((char*)out_buffer,(char*)out_buffer+BLOCK); // allow reading of more data

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

/*CONSTRUCTORS / DECONSTRUCTORS*/

HuffmanBuffer::HuffmanBuffer(std::streambuf* buffer): buffer(buffer) {
    huffman = new HuffmanAlgorithm();

    in_buffer = new uint8_t[BLOCK];
    out_buffer = new uint8_t[BLOCK];
    code_bits = new uint8_t[BLOCK];

    for (int i = 0; i < BLOCK; i++) {
        in_buffer[i] = 0;
        out_buffer[i] = 0;
        code_bits[i] = 0;
    }

    //char* _tempcast = (char*)in_buffer;
    char* _tempcast2 = (char*)out_buffer;

    setg(0,0,0);
    setp(_tempcast2,_tempcast2+BLOCK);

    bit_idx = 0;
}

HuffmanBuffer::~HuffmanBuffer() {
    delete[] in_buffer;
    delete[] out_buffer;
    delete[] code_bits;
    delete huffman;
}

/*ACCESS FUNCTIONS*/

void HuffmanBuffer::set_huffman(std::istream* input, std::ostream* dst) {
    huffman->set_encode(input);
    huffman->write_header(dst);
}

void HuffmanBuffer::set_huffman(std::ostream* input) {
    return;
}
