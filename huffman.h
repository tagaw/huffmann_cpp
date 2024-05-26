#pragma once

#include "constants.h"
#include "codes.h"
#include "node.h"
#include "queue.h"

class HuffmanAlgorithm {
private:
    Code table[ASCII];
    TreeNode* root;
    PriorityQueue pq;

    std::ifstream* infile;

    void read_tree();

    void make_tree(int histogram[ASCII]);

    void generate_histogram();

    void generate_codes();

public:
    // Constructors
    HuffmanAlgorithm(std::ifstream ifs);

    ~HuffmanAlgorithm();

    // Access
    Code* get_table();
};