#include "Memory.h"
#include <algorithm>

Memory::Memory(Screen& screenRef) : screen(screenRef), cells(SIZE, 0) {}

void Memory::load(const std::vector<int>& program, int startAddress) {
    for (size_t i = 0; i < program.size(); ++i) {
        int addr = startAddress + static_cast<int>(i * 2);  // Each instruction takes 2 cells
        if (addr >= 0 && (addr + 1) < SIZE) {
            cells[addr]     = (program[i] >> 8) & 0xFF;     // High byte
            cells[addr + 1] = program[i] & 0xFF;            // Low byte
        }
    }
}

void Memory::store(int address, int value) {
    if (address == 0x00) {
        // Memory-mapped I/O: writing to address 0x00 goes to the screen.
        screen.write(value);
    } else if (address >= 0 && address < SIZE) {
        cells[address] = value & 0xFF;
    }
}

int Memory::read(int address) const {
    if (address == 0x00) {
        // Memory-mapped I/O: reading address 0x00 returns the screen's last value.
        return screen.getLastValue();
    } else if (address > 0 && address < SIZE) {
        return cells[address];
    }
    return 0;
}

int Memory::get(int address) const {
    return read(address);
}

void Memory::reset() {
    std::fill(cells.begin(), cells.end(), 0);
}

int Memory::size() const {
    return SIZE;
}
