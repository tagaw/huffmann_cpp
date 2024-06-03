#pragma once
#include "buffer.h"
#include "huffman.h"


class EncodeStream : public std::ostream {
private:
    HuffmanAlgorithm* huffman;
    std::ostream* base_stream;

    uint8_t input[BLOCK];
    uint8_t output[BLOCK];

    int bit_idx;
    int max_code_bit = BLOCK * 8;

    void flush_code(std::ostream& out);

    void compress(int nbytes, std::ostream& out);

public:
    EncodeStream(std::ostream* infile);  

    ~EncodeStream();

    // overload 
    friend std::ostream& operator<<(EncodeStream& ofile, std::istream& ifile);

};