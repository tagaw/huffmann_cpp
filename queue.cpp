#include "queue.h"

int PriorityQueue::parent(int n) {
    return n / 2;
}

int PriorityQueue::l_child(int n) {
    return (2 * n) + 1;
}

int PriorityQueue::r_child(int n) {
    return 2*(n+1);
}

void PriorityQueue::upheap(int n) {
    while (n > 0 && (*queue[n] < *queue[parent(n)])) {
        std::swap(queue[parent(n)],queue[n]);
        n = parent(n);
    }
}

void PriorityQueue::downheap() {
    int n = 0;
    int smallest = 0;
    int size = queue.size();
    while (l_child(n) < size) {
        if (r_child(n) == size) {
            smallest = l_child(n);
        }
        else {
            if (*queue[l_child(n)] < *queue[r_child(n)]) {
                smallest = l_child(n);
            }
            else {
                smallest = r_child(n);
            }
        }
        std::swap(queue[n],queue[smallest]);
        n = smallest;
    }
}

// Constructors

PriorityQueue::PriorityQueue(const PriorityQueue& pq) {
    /*Copy constructor*/
    queue = pq.queue;
}

void PriorityQueue::enqueue(TreeNode* n) {
    int idx = queue.size();   
    queue.push_back(n);
    upheap(idx);

}

TreeNode* PriorityQueue::dequeue() {
    if (queue.empty()) {
        return nullptr;
    }
    TreeNode* retval = queue[0];
    // Swaps popped node and last node, deletes popped node
    std::swap(queue[0],queue.back());
    queue.pop_back();
    // calls downheap after putting heaviest node on top
    downheap();
    return retval;
}


std::ostream& operator<<(std::ostream& stream, PriorityQueue& pq ) {
    int lvl = 0;
    std::string s = "";
    int size = pq.queue.size();
    for (int i = 0; i < size; i++) {
        if (i > lvl) {
            s += '\n';
            lvl = pq.r_child(i-1);
        }
        s += pq.queue[i]->to_string() + "\t";
    }
    return stream << s << std::endl;
}



