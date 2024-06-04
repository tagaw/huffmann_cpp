#pragma once

#include <cstdint>
#include <iostream>

#define BLOCK 4096
#define ASCII 256
#define MAX_CODE (ASCII / 8)
#define MAGIC_NUMBER 0xDEADBEEF

typedef struct {
    uint32_t magic;
    uint32_t tree_size;
    uint32_t file_size;
} Header;

