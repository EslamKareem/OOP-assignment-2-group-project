#include "InstructionDecoder.h"
Instruction InstructionDecoder::decode(uint8_t high, uint8_t low)
{
    uint8_t op = (high >> 4) & 0x0F;
    uint8_t r = (high >> 2) & 0x03;
    uint8_t s = (high & 0x03);
    uint8_t t = (low >> 6) & 0x03;
    uint8_t xy = low & 0x3F;
    uint16_t raw = (high << 8) | low;

    bool valid = true;
    if (op < 1) valid = false;
    if (r > 3) valid = false;
    if (s > 3) valid = false;
    if (t > 3) valid = false;
    if (xy > 63) valid = false;

    return Instruction(static_cast<Opcode>(op), r, s, t, xy, raw, valid);
}

Instruction InstructionDecoder::decodeWord(uint16_t word)
{
    uint8_t high = static_cast<uint8_t>((word >> 8) & 0xFF);
    uint8_t low  = static_cast<uint8_t>(word & 0xFF);
    return decode(high, low);
}