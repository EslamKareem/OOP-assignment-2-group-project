#include "ALU.h"

ALU::ALU()
{
}

int ALU::addTowscomplement(int a, int b)
{
    int result = a + b;

    return result & 0xFF;        
}

int ALU::bitwiseAnd(int a, int b)
{
    return (a & b) & 0xFF;
}

int ALU::bitwiseOr(int a, int b)
{
    return (a ^ b) & 0xFF;
}


int ALU::addFloatingPoint(int a, int b) 
{
    int sum = a + b;
    return sum & 0xFF;
}
int ALU::rotateRight(int value, int shiftCount)
{
    value &= 0xFF;
    shiftCount %= 8;
    int rotated = (value >> shiftCount) | (value << (8 - shiftCount));
    return rotated & 0xFF;
}