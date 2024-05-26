#include "huffman.h"
#include <queue>

struct customCmpLs {
    bool operator() (const TreeNode* n1, const TreeNode* n2) const { 
        return n1->freq > n2->freq; 
    }
};

void HuffmanAlgorithm::make_tree(int histogram[ASCII]) {
    if (histogram[0] == 0) { //ensures that 2 nodes exist
        histogram[0] = 1;
    }
    if (histogram[1] == 0) {
        histogram[1] = 1;
    }
    std::priority_queue<TreeNode*, std::vector<TreeNode*>,customCmpLs> pq;
    for (int i = 0; i < ASCII; i++) { // create a priority queue
        if (histogram[i] > 0) {
            pq.push(new TreeNode((uint8_t)i,histogram[i]));
        }
    }

    TreeNode* l,*r; 
    while (pq.size() > 1) { // create huffman tree
        l = pq.top();
        pq.pop();
        r = pq.top();
        pq.pop();

        pq.push(new TreeNode(l,r)); // joins 2 child nodes, enqueues parent
    }

    root = pq.top(); // set root
    pq.pop();

}

void HuffmanAlgorithm::generate_histogram() {
    int histogram[ASCII] = {0};
    uint8_t temp[BLOCK];
    infile->read((char*)temp,BLOCK);
    int bytes_read = infile->gcount();
    while ( bytes_read > 0) {
        for (int i = 0; i < bytes_read; i++) {
            int sym = temp[i];
            histogram[sym] += 1;
        }
        infile->read((char*)temp,BLOCK);
        int bytes_read = infile->gcount();
    }
    make_tree(histogram);

    infile->seekg(std::ios_base::beg);
}

void HuffmanAlgorithm::generate_codes(TreeNode* root, Code c) {
    if (root->left == nullptr && root->right == nullptr) {
        table[(int)root->symbol] = c;
        return
    }
    if (root->left) {
        c.push_bit(0);
        generate_codes(root->left,c);
    }
    c.pop_bit()
    if (root->right) {
        c.push_bit(1);
        generate_codes(root->right,c);
    }
    return;
}

HuffmanAlgorithm::HuffmanAlgorithm(std::ifstream ifs) {
    infile = &ifs;
    root = nullptr;
}

HuffmanAlgorithm::~HuffmanAlgorithm() {
    
}

Code* HuffmanAlgorithm::get_table() {
    return table;
}