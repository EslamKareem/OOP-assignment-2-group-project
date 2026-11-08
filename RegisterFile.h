#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

#include <array>
#include <cstdint>
#include <iostream>
using namespace std;

// RegisterFile holds 16 x 8-bit registers (R0..R15) for the Vole machine.
// Required by CPU.h and machine.h.
class RegisterFile {
public:
    static const int NUM_REGISTERS = 16;

    RegisterFile();

    uint8_t read(int index) const;
    void write(int index, uint8_t value);
    void reset();
    string dump()const;

private:
    int registers[NUM_REGISTERS];
};

#endif // REGISTER_FILE_H
