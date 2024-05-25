#pragma once

#include "constants.h"
#include "codes.h"
#include "node.h"
#include "queue.h"

class HuffmanAlgorithm {
private:
    Code* table[ASCII];
    TreeNode* root;
    PriorityQueue pq;

public:
    // Constructors
    HuffmanAlgorithm(std::ifstream infile);

    ~HuffmanAlgorithm();

    // Access
    Code* get_table();
};