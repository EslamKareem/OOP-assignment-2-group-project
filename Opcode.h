#pragma once
#include <cstdint>

enum class Opcode : uint8_t {
    LOAD_MEM = 0x1,
    LOAD_IMM = 0x2,
    STORE = 0x3,
    MOVE = 0x4,
    ADD_INT = 0x5,
    ADD_FLOAT = 0x6,
    OR_OP = 0x7,
    AND_OP = 0x8,
    XOR_OP = 0x9,
    ROTATE = 0xA,
    JUMP_EQ = 0xB,
    HALT = 0xC,
};
