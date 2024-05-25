#pragma once

#include "huffman.h"

// @brief A buffer that handles I/O of huffman data
class HuffmanBuffer : public std::streambuf {
private:
    std::streambuf* buffer;

    uint8_t* in_buffer;
    uint8_t* out_buffer;

    HuffmanAlgorithm* huffman;

    int bit_idx;
    const int max_bit = BLOCK * 8;

    void compress();

protected:
    virtual std::streambuf::int_type underflow();

    virtual std::streambuf::int_type overflow(int c = EOF);

    virtual std::streambuf::int_type sync();

public:
    HuffmanBuffer(std::streambuf* buffer, HuffmanAlgorithm* hfa);

    ~HuffmanBuffer();

};
