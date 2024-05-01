#pragma once

#include <cstdint>
#include <vector>
#include "node.h"


class PriorityQueue { 
    // implemented as a min-heap

private: 
    // actual data container
    std::vector<TreeNode*> queue;

    int parent(int n);

    int l_child(int n);
    
    int r_child(int n);

    void upheap(int n);

    void downheap();

public:

    PriorityQueue() {};

    PriorityQueue(const PriorityQueue& pq);

    ~PriorityQueue() {};

    // access

    void enqueue(TreeNode* n);

    TreeNode* dequeue();

    // Debugging

    friend std::ostream& operator<<(std::ostream& stream, PriorityQueue& pq );
 
};
