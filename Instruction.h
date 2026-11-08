#pragma once
#include "Opcode.h"
#include <cstdint>

class Instruction
{
private:
    Opcode opcode;
    uint8_t r;
    uint8_t s;
    uint8_t t;
    uint8_t xy;
    uint16_t raw;
    bool valid;

    
    
public:
    Instruction(Opcode opcode, uint8_t r, uint8_t s, uint8_t t, uint8_t xy, uint16_t raw, bool valid);
    
    Opcode getOpcode() const;
    uint8_t getR() const;
    uint8_t getS() const;
    uint8_t getT() const;
    uint8_t getXY() const;
    uint16_t getRaw() const;
    uint16_t  getAddress() const;
    uint16_t getConstant() const;
    uint16_t getMoveDest() const;
    uint16_t getRotateCount() const;
    bool isValid() const;
    
  
};



