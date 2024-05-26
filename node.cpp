#include "node.h"

// Constructors

TreeNode::TreeNode(uint8_t symbol, int freq) {
    this->symbol = symbol;
    this->freq = freq;
    this->left = nullptr;
    this->right = nullptr;
}

TreeNode::TreeNode(TreeNode* l, TreeNode* r) {
    this->symbol = '$';
    this->freq = l->freq + r->freq;
    this->left = l;
    this->right = r;
}

TreeNode::TreeNode(const TreeNode& n) {
    this->symbol = n.symbol;
    this->freq = n.freq;
    this->left = nullptr;
    this->right = nullptr;
}

TreeNode::~TreeNode() {}

// Access
std::string TreeNode::to_string() {
    std::string str = "{ ";
    str += this->symbol;
    str += " : ";
    str += std::to_string(this->freq);
    str += " }";
    return str;
}

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
        this->left = n.left;
        this->right = n.right;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& stream, TreeNode& n) { 
    return stream << n.to_string();
}

