#pragma once

#include "huffman.h"

// @brief A buffer that handles I/O of huffman data. Decodes read input and Encodes written output
class HuffmanBuffer : public std::streambuf {
private:
    // underlying buffer
    std::streambuf* buffer;

    // buffers
    uint8_t* in_buffer;
    uint8_t* out_buffer;
    uint8_t* code_bits;

    HuffmanAlgorithm* huffman;

    int bit_idx;
    const int max_bit = BLOCK * 8;

    // @brief performs huffman compression of n bytes
    void compress(int bytes_in);

    // @brief finishes and flushes codes in code buffer
    void finish_code();

protected:
    // @brief decodes characters for reading
    //virtual std::streambuf::int_type underflow();

    // @brief encodes characters for writing
    virtual std::streambuf::int_type overflow(int c = EOF);

    // @brief syncs buffer with file, flushes data and codes
    virtual std::streambuf::int_type sync();

public:
    // @brief Wraps an existing buffer and assigns associated huffman algorithm
    HuffmanBuffer(std::streambuf* buffer);

    // @brief Clears all allocated data
    virtual ~HuffmanBuffer();

    //@brief Sets internal huffman object for encoding
    //@param istream* Input data for encoding
    void set_huffman(std::istream* input, std::ostream* dst);

    //@brief Sets internal huffman object for decoding
    //@param ostream* Input data for decoding
    void set_huffman(std::ostream* input, std::istream* dst);
};
