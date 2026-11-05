#include "Instruction.h"

Instruction::Instruction(Opcode opcode, uint8_t r, uint8_t s, uint8_t t, uint8_t xy, uint16_t raw, bool valid)
    : opcode(opcode), r(r), s(s), t(t), xy(xy), raw(raw), valid(valid)
{
}

Opcode Instruction::getOpcode() const
{
    return opcode;
}

uint8_t Instruction::getR() const
{
    return r;
}

uint8_t Instruction::getS() const
{
    return s;
}

uint8_t Instruction::getT() const
{
    return t;
}

uint8_t Instruction::getXY() const
{
    return xy;
}

uint16_t Instruction::getRaw() const
{
    return raw;
}

bool Instruction::isValid() const
{
    return valid;
}
