#include "node.h"

// Constructors

TreeNode::TreeNode(uint8_t symbol, int freq) {
    this->symbol = symbol;
    this->freq = freq;
    this->left = nullptr;
    this->right = nullptr;
}

TreeNode::TreeNode(const TreeNode& n) {
    this->symbol = n.symbol;
    this->freq = n.freq;
    this->left = nullptr;
    this->right = nullptr;
}

TreeNode::~TreeNode() {}

// Overloads

bool TreeNode::operator==(const TreeNode& n) {
    return (this->freq == n.freq);
}

bool TreeNode::operator<(const TreeNode& n) {
    return (this->freq < n.freq);
}

bool TreeNode::operator>(const TreeNode& n) {
    return (this->freq > n.freq);
}

TreeNode& TreeNode::operator=(const TreeNode& n) {
    if (&n != this) {
        this->symbol = n.symbol;
        this->freq = n.freq;
        this->left = nullptr;
        this->right = nullptr;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& stream, TreeNode& n) { 
    return stream << "{ " << n.symbol << " : " << n.freq << " }" << std::endl;
}

std::ostream& operator<<(std::ostream& stream, TreeNode* n) { 
    return stream << "{ " << n->symbol << " : " << n->freq << " }" << std::endl;
}

