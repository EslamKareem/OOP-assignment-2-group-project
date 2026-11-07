#ifndef ALU_H
#define ALU_H

#include <cstdint>

// ALU (Arithmetic Logic Unit) for the Vole machine.
// Required by CPU.h and machine.h.
class ALU {
public:
    ALU() = default;

    uint8_t addInt(uint8_t a, uint8_t b) const;
    uint8_t addFloat(uint8_t a, uint8_t b) const;
    uint8_t opOr(uint8_t a, uint8_t b) const;
    uint8_t opAnd(uint8_t a, uint8_t b) const;
    uint8_t opXor(uint8_t a, uint8_t b) const;
    uint8_t rotate(uint8_t value, uint8_t n) const;
};

#endif // ALU_H
