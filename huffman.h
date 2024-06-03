#pragma once

#include "constants.h"
#include "codes.h"
#include "node.h"
#include "queue.h"

class HuffmanAlgorithm {
private:
    Code table[ASCII];
    TreeNode* root;

    Header header;

    // @brief input for huffman encoding (compression)
    std::istream* infile; 
    // @brief True if current object is set for encoding
    bool encoding;

    //@brief input for huffman decoding (decompression)    
    std::ostream* outfile; 
    //@brief True if current object is set for decoding
    bool decoding;

    // @brief reconstructs a tree from an encoded file. -
    // Used in set_decode()
    void read_tree();

    // @brief helper function used to make a huffman tree from an ASCII histogram -
    // Used in generate_histogram();
    void make_tree(int histogram[ASCII]);

    // @brief helper function used to delete a tree -
    // Used in deconstructor
    void del_tree(TreeNode* root);

    //@brief Reads in a file, generates a histogram of ASCII, creates a huffman tree - 
    // Used in set_encode()
    void generate_histogram();

    //@brief Uses a generated huffman tree to create a code table
    void generate_codes(TreeNode* root, Code c);

    //@brief Writes a tree to a set file
    void write_tree(TreeNode* root, std::ostream& outfile);

public:
    // Constructor -
    // @param input File to encode/decode

    HuffmanAlgorithm();

    // Deconstructor -
    // @brief Deletes a tree if initialized
    ~HuffmanAlgorithm();

    // @brief access the code table
    Code* get_table();

    // @brief Intialize the object for encoding
    void set_encode(std::istream* input);

    //@brief Initialize the object for decoding
    void set_decode(std::ostream& input);

    //@brief Writes a header to a specified file
    void write_header(std::ostream& outfile);
    
};