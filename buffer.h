#pragma once

#include "huffman.h"

// @brief A buffer that handles I/O of huffman data
class HuffmanBuffer : public std::streambuf {
private:
    std::streambuf* buffer;

    uint8_t* in_buffer;
    uint8_t* out_buffer;
    uint8_t* code_bits;

    HuffmanAlgorithm* huffman;

    int bit_idx;
    const int max_bit = BLOCK * 8;

    // @brief performs huffman compression of n bytes
    void compress(int bytes_in);

    // @brief flushes codes to location
    void finish_code();

protected:
    // @brief gets characters in buffer for reading
    //virtual std::streambuf::int_type underflow();

    // @brief gets characters in buffer for writing
    virtual std::streambuf::int_type overflow(int c = EOF);

    // @brief syncs location in file with buffer
    virtual std::streambuf::int_type sync();

public:
    // @brief Wraps an existing buffer and assigns associated huffman algorithm
    HuffmanBuffer(std::streambuf* buffer, HuffmanAlgorithm* hfa);

    // @brief Clears all allocated data
    virtual ~HuffmanBuffer();

    //@brief set HuffmanAlgorithm to new data
    void set_huffman(HuffmanAlgorithm* new_ha);

    void set_encode();

};
