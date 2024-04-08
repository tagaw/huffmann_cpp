#pragma once

#include <cstdint>
#include <iostream>

class TreeNode {

public:
    // Node data
    uint8_t symbol;
    int freq;
    TreeNode* left;
    TreeNode* right;
    // Constructors & Destructors
    
    /*
    @brief Creates a new TreeNode with symbol and frequency. Left/Right nodes set to nullptr 
    @param symbol | ASCII symbol
    @param freq | frequency of ASCII symbol
    */
    TreeNode(uint8_t symbol, int freq);

    TreeNode(const TreeNode& n);

    ~TreeNode();

    // Overloads

    bool operator==(const TreeNode& n);

    bool operator>(const TreeNode& n);

    bool operator<(const TreeNode& n);

    TreeNode& operator=(const TreeNode& n);

    friend std::ostream& operator<<(std::ostream& stream, TreeNode& n );

    friend std::ostream& operator<<(std::ostream& stream, TreeNode* n );
};
