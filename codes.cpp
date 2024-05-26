#include "codes.h"

Code::Code(void) {
    this->top = 0;
}

int Code::size() {
    return top;
}

bool Code::empty() {
    return top == 0;
}

bool Code::full() {
    return top > ASCII;
}

void Code::set_bit(int i) {
    if (i > 255) {
        i = 255;
    }
    bits[i/8] |= (uint8_t)1 << (i%8);
}

void Code::clear_bit(int i) {
    if (i > 255) {
        i = 255;
    }
    bits[i/8] &= ~((uint8_t)1 << (i%8));
}

uint8_t Code::get_bit(int i) {
    if (i > 255) {
        i = 255;
    }
    uint8_t bit = bits[i/8] & (uint8_t)1 << (i%8);
    if (bit) return 1;
    return 0;
}

void Code::push_bit(uint8_t bit) {
    if (bit) {
        set_bit(top);
    }
    else {
        clear_bit(top);
    }
    top += 1;
    return;
}

uint8_t Code::pop_bit(void) {
    top -= 1;
    return get_bit(top);
}

Code& Code::operator=(const Code& c) {
    if (this != &c) {
        top = c.top;
        for (int i = 0; i < (top+8)/8; i++) {
            bits[i] = c.bits[i];
        }
    }
    return *this;
}
