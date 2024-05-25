#include <iostream>
#include "buffer.h"

void set_i_bit(uint8_t* bit_array, int i) {
    bit_array[i/8] |= (uint8_t)1 << (i % 8);
    return;
}

void clr_i_bit(uint8_t* bit_array, int i) {
    bit_array[i/8] &= ~((uint8_t)1 << (i % 8));
    return;
}

HuffmanBuffer::HuffmanBuffer(std::streambuf* buffer, HuffmanAlgorithm* hfa): buffer(buffer) {
    huffman = hfa;

    in_buffer = new uint8_t[BLOCK];
    out_buffer = new uint8_t[BLOCK];

    char* _tempcast = (char*)in_buffer;
    char* _tempcast2 = (char*)out_buffer;

    setg(0,0,0);
    setp(_tempcast2,_tempcast2+BLOCK);

    bit_idx = 0;
}

HuffmanBuffer::~HuffmanBuffer() {
    delete[] in_buffer;
    delete[] out_buffer;
}

void HuffmanBuffer::compress() {
    Code* table = huffman->get_table();
    int bytes_in = gptr() - eback();
    for (int i = 0; i < bytes_in; i++) {
        int symb = in_buffer[i];
        Code c = table[symb];
        for (int j = 0; j < c.size(); j++) {
            if (bit_idx >= max_bit)  {
                sputn((char*)out_buffer,BLOCK-1);
                bit_idx = 0;
            }
            if (c.get_bit(i)) {
                set_i_bit(out_buffer,bit_idx);
            }
            else {
                clr_i_bit(out_buffer,bit_idx);
            }
            bit_idx += 1;
        }
    }
}