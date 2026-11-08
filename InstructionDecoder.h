#pragma once
#include <cstdint>
#include "Instruction.h"
class InstructionDecoder{
public:
    static Instruction decode(uint8_t high, uint8_t low);
    static Instruction decodeWord(uint16_t word);
};


