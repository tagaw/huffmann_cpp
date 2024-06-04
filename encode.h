#pragma once
#include "buffer.h"
#include "huffman.h"


class EncodeStream : public std::ostream {
private:
    // base stream for unformatted i/o
    std::ostream* base_stream;

    // pointer to current buffer
    HuffmanBuffer* curr_buffer;

public:
    //@brief constructor, uses existing ostream
    EncodeStream(std::ostream* infile);  

    //@brief deconstructor
    ~EncodeStream();

    //@brief Insertion into stream encodes data
    friend std::ostream& operator<<(EncodeStream& ofile, std::istream& ifile);

};