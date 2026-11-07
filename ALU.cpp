#include "ALU.h"

uint8_t ALU::addInt(uint8_t a, uint8_t b) const {
    return static_cast<uint8_t>(static_cast<int>(a) + static_cast<int>(b));
}

uint8_t ALU::addFloat(uint8_t a, uint8_t b) const {
    return static_cast<uint8_t>(static_cast<int>(a) + static_cast<int>(b));
}

uint8_t ALU::opOr(uint8_t a, uint8_t b) const {
    return static_cast<uint8_t>(a | b);
}

uint8_t ALU::opAnd(uint8_t a, uint8_t b) const {
    return static_cast<uint8_t>(a & b);
}

uint8_t ALU::opXor(uint8_t a, uint8_t b) const {
    return static_cast<uint8_t>(a ^ b);
}

uint8_t ALU::rotate(uint8_t value, uint8_t n) const {
    n &= 0x07;
    if (n == 0) return value;
    return static_cast<uint8_t>((value << n) | (value >> (8 - n)));
}
