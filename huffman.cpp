#include "huffman.h"
#include <queue>

struct customCmpLs {
    bool operator() (const TreeNode* n1, const TreeNode* n2) const { 
        return n1->freq > n2->freq; 
    }
};

void HuffmanAlgorithm::make_tree(int histogram[ASCII]) {
    //ensures that 2 nodes exist
    if (histogram[0] == 0) { 
        histogram[0] = 1;
    }
    if (histogram[1] == 0) {
        histogram[1] = 1;
    }

    // create a priority queue
    std::priority_queue<TreeNode*, std::vector<TreeNode*>,customCmpLs> pq;
    for (int i = 0; i < ASCII; i++) { 
        if (histogram[i] > 0) {
            pq.push(new TreeNode((uint8_t)i,histogram[i]));
        }
    }

    // create huffman tree
    TreeNode* l,*r; 
    while (pq.size() > 1) { // joins 2 child nodes, enqueues parent
        l = pq.top();
        pq.pop();
        r = pq.top();
        pq.pop();

        pq.push(new TreeNode(l,r)); 
    }

    root = pq.top(); // set root
    pq.pop();

}

void HuffmanAlgorithm::del_tree(TreeNode* root) {
    // Deletes a tree in pre-fix order
    if (root->left == nullptr and root->right == nullptr) {
        delete root;
        return;
    }
    if (root->left) {
        del_tree(root->left);
    }
    if (root->right) {
        del_tree(root->right);
    }
    delete root;
}

void HuffmanAlgorithm::generate_histogram() {
    int histogram[ASCII] = {0};
    uint8_t temp[BLOCK];
    int file_size = 0;
    int bytes_read;

    // do {
    //     for (int i = 0; i < bytes_read; i++) {
    //         int sym = temp[i];
    //         histogram[sym] += 1;
    //     }
    //     infile->read((char*)temp,BLOCK);
    //     bytes_read = infile->gcount();
    //     file_size += bytes_read;
    // } while (!infile->eof());

    infile->read((char*)temp,BLOCK);
    bytes_read = infile->gcount();
    file_size += bytes_read;
    while ( bytes_read > 0 ) {
        for (int i = 0; i < bytes_read; i++) {
            int sym = temp[i];
            histogram[sym] += 1;
        }
        infile->read((char*)temp,BLOCK);
        bytes_read = infile->gcount();
        file_size += bytes_read;
    }

    // makes a tree from file contents
    make_tree(histogram);

    // sets tree size and file length for decoding
    int leaf_ct = 0;
    for (int i = 0; i < ASCII; i++) {
        if (histogram[i] > 0) {
            leaf_ct += 1;
        }
    }
    header.file_size = file_size;
    header.tree_size = (3*leaf_ct) -1;

    // clears the EOF bit, allows for re-reading
    infile->clear();
    
    infile->seekg(0, std::ios::beg);
}

void HuffmanAlgorithm::generate_codes(TreeNode* root, Code c) {
    // pre-fix tree traversal for code generation
    if (root->left == nullptr && root->right == nullptr) {
        table[(int)root->symbol] = c;
        return;
    }
    if (root->left != nullptr) {
        c.push_bit(0);
        generate_codes(root->left,c);
    }
    c.pop_bit();
    if (root->right != nullptr) {
        c.push_bit(1);
        generate_codes(root->right,c);
    }
    return;
}

HuffmanAlgorithm::HuffmanAlgorithm() {
    infile = nullptr;
    encoding = false;

    outfile = nullptr;
    decoding = false;

    root = nullptr;
    header.magic = MAGIC_NUMBER;
}


HuffmanAlgorithm::~HuffmanAlgorithm() {
    if (root != nullptr) {
        del_tree(root);
    }
}

Code* HuffmanAlgorithm::get_table() {
    return table;
}

void HuffmanAlgorithm::write_tree(TreeNode* root, std::ostream& outfile) {
    // dumps tree in pre-fix order
    if (root != nullptr) {
        if (root->left == nullptr && root->right == nullptr) {
            outfile.write("L",1);
            outfile.write((char*)&(root->symbol),1);
            return;
        }
        if (root->left) {
            write_tree(root->left,outfile);
        }
        if (root->right) {
            write_tree(root->right,outfile);
        }
        outfile.write("I",1);
        return;
    }
}

void HuffmanAlgorithm::set_encode(std::istream* input) {
    // toggle algorithm for encoding purposes
    decoding = false;
    encoding = true;

    infile = input;
    generate_histogram();

    Code c;
    generate_codes(root, c);

    return;
}

void HuffmanAlgorithm::write_header(std::ostream& outfile) {
    if (encoding) {
        outfile.write((char*)&header,sizeof(header));
        write_tree(root,outfile);
    }
    else {
        throw std::logic_error("Cannot write header, Object not set for encoding");
    }
    return;
}