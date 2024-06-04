#include "encode.h"

EncodeStream::EncodeStream(std::ostream* infile) : std::ostream(new HuffmanBuffer(infile->rdbuf()))
{   
    curr_buffer = (HuffmanBuffer*)rdbuf();
    base_stream = infile;
}

EncodeStream::~EncodeStream() {
    delete rdbuf();
}

std::ostream& operator<<(EncodeStream& ofile, std::istream& ifile) {
    char i_buffer[BLOCK];
    int bytes_read;

    std::istream* src = &ifile;
    std::ostream* dst = ofile.base_stream;

    // set buffer for encoding
    ofile.curr_buffer->set_huffman(src,dst);    

    // buffered i/o
    ifile.read(i_buffer,BLOCK);
    bytes_read = ifile.gcount();

    while ( bytes_read > 0 ) {
        ofile.write(i_buffer,bytes_read);

        ifile.read(i_buffer,BLOCK);
        bytes_read = ifile.gcount();
    }

    ofile.flush();
    return ofile;
}