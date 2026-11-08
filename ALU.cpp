#include "ALU.h"

ALU::ALU()
{
}

int ALU::addTwosComplement(int a, int b)
{
    int result = a + b;
    return result & 0xFF;
}

int ALU::addFloat(int a, int b)
{
    int sum = a + b;
    return sum & 0xFF;
}

int ALU::bitOr(int a, int b)
{
    return (a | b) & 0xFF;
}

int ALU::bitAnd(int a, int b)
{
    return (a & b) & 0xFF;
}

int ALU::bitXor(int a, int b)
{
    return (a ^ b) & 0xFF;
}

int ALU::rotateRight(int value, int steps)
{
    value &= 0xFF;
    steps %= 8;
    int rotated = (value >> steps) | (value << (8 - steps));
    return rotated & 0xFF;
}

double ALU::toFloat(int bits)
{
    (void)bits;
    return 0.0;
}

int ALU::fromFloat(double value)
{
    (void)value;
    return 0;
}
