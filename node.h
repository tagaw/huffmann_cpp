#pragma once

#include <cstdint>
#include <string>
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

    /*
    @brief Creates a parent of 2 children with a frequency equal to both children.
    @param l | left child
    @param r | right childn
    */
    TreeNode(TreeNode* l, TreeNode* r);

    TreeNode(const TreeNode& n);

    ~TreeNode();

    // Access
    std::string to_string();

    // Overloads

    bool operator==(const TreeNode& n);

    bool operator>(const TreeNode& n);

    bool operator<(const TreeNode& n);

    TreeNode& operator=(const TreeNode& n);

    friend std::ostream& operator<<(std::ostream& stream, TreeNode& n );
};
