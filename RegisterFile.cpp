#include "RegisterFile.h"

RegisterFile::RegisterFile() {
    regs.fill(0);
}

uint8_t RegisterFile::read(int index) const {
    if (index >= 0 && index < NUM_REGISTERS) {
        return regs[index];
    }
    return 0;
}

void RegisterFile::write(int index, uint8_t value) {
    if (index >= 0 && index < NUM_REGISTERS) {
        regs[index] = value;
    }
}

void RegisterFile::reset() {
    regs.fill(0);
}
