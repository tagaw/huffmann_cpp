#include "encode.h"

// @brief sets ith bit in array
// void set_i_bit(uint8_t* bit_array, int i) {
//     bit_array[i/8] |= (uint8_t)1 << (i % 8);
//     return;
// }

// // @brief clears ith bit in array
// void clr_i_bit(uint8_t* bit_array, int i) {
//     bit_array[i/8] &= ~((uint8_t)1 << (i % 8));
//     return;
// }

EncodeStream::EncodeStream(std::ostream* infile) : std::ostream(new HuffmanBuffer(infile->rdbuf(), huffman)),
huffman(new HuffmanAlgorithm()) 
{   
    base_stream = infile;
    //huffman->set_encode();
    bit_idx = 0;
}

// void EncodeStream::flush_code(std::ostream& out) {
//     if (bit_idx < max_code_bit) {
//         for (int i = bit_idx % 8; i > 0; i = (i+1)%8 ) {
//             clr_i_bit(output,bit_idx);
//             bit_idx += 1;
//         }
//     }
//     out.write((char*)output,bit_idx/8);
    
//     // std::cerr.write((char*)output,BLOCK);
//     // try
//     // {
     
//     //   out.exceptions(std::ios_base::badbit | std::ios::failbit);
//     //   if (out.bad()) {
//     //     std::cout << "bruh\n";
//     //   }
//     // }
//     // catch (const std::ios_base::failure& e)
//     // {
//     //   std::cerr << "error: " << e.what() << std::endl;
//     //   //std::cerr << "error: " << e.code().message() << std::endl;
//     //   return;
//     // }
// }

// void EncodeStream::compress(int nbytes, std::ostream& out) {
//     Code* table = huffman->get_table();
//     for (int i = 0; i < nbytes; i++) {
//         int symbol = input[i];
//         Code c = table[symbol];

//         for (int j = 0; j < c.size(); j++) {
//             if (bit_idx >= max_code_bit)  {
//                 flush_code(out);
//                 bit_idx = 0;
//             }
//             if (c.get_bit(j)) {
//                 set_i_bit(output,bit_idx);
//             }
//             else {
//                 clr_i_bit(output,bit_idx);
//             }
//             bit_idx += 1;
//         }
//     }
// } 

EncodeStream::~EncodeStream() {
    delete huffman;
}

// std::istream& operator>>(EncodeStream& infile, std::ostream& ofile) {
//     infile.huffman->write_header(ofile);

//     infile.read((char*)infile.input,BLOCK);
//     int bytes_read = infile.gcount();
    
//     // read bytes, compress, read in more, flush
//     while ( bytes_read > 0 ) {
//         infile.compress(bytes_read,ofile);
//         infile.read((char*)infile.input,BLOCK);
//         bytes_read = infile.gcount();
//     }
//     infile.flush_code(ofile);

//     return infile;
// }

std::ostream& operator<<(EncodeStream& ofile, std::istream& ifile) {
    char bruh[BLOCK];
    HuffmanBuffer* curr = (HuffmanBuffer*)ofile.rdbuf();
    curr->set_huffman(new HuffmanAlgorithm(&ifile));
    curr->set_encode();
    ifile.read(bruh,BLOCK);
    int bytes_read = ifile.gcount();
    while ( bytes_read > 0) {
        ofile.write(bruh,bytes_read);
        ifile.read(bruh,BLOCK);
        bytes_read = ifile.gcount();
    }
    ofile.flush();
    return ofile;
}