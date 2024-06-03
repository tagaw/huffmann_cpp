#pragma once
#include <cstdint>
#include <iostream>

#define BLOCK 4096
#define ASCII 256
#define MAX_CODE (ASCII / 8)
#define MAGIC_NUMBER 0xDEADBEEF

typedef struct {
    uint32_t magic;
    uint16_t tree_size;
    uint64_t file_size;
    void print_h(void) {
        std::cerr << magic << "\n" << tree_size << "\n" << file_size << std::endl;
    } 
} Header;
