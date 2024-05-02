#pragma once

#include <cstdint>
#include <fstream>
#include <iostream>
#include "constants.h"

// @brief A code class that functions as a way to represent binary codes of a huffman tree.
// Works as a stack of 'bits' to build up a code
class Code { 
private:
    int top;
    uint8_t bits[MAX_CODE]; // each element is a 0/1 to represent code

    void set_bit(int i);

    void clear_bit(int i);

    uint8_t get_bit(int i);

public:
    Code(void);

    // access
    int size();

    bool empty();

    bool full();

    void push_bit(uint8_t bit);

    uint8_t pop_bit();
};
