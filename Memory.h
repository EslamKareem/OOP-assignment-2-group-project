#ifndef MEMORY_H
#define MEMORY_H

#include <vector>
#include "Screen.h"

// Memory (RAM) for the Vole machine: 256 byte-addressable cells.
// Address 0x00 is memory-mapped I/O to the Screen: storing to 0x00 writes
// the value to the screen instead of keeping it in RAM.
class Memory {
private:
    static const int SIZE = 256;
    std::vector<int> cells;
    Screen& screen;

public:
    // Construct wired to the given output screen.
    // Called by Machine as: memory(screen)
    explicit Memory(Screen& screenRef);
    ~Memory() = default;

    // Load a program (vector of 16-bit instruction words) starting at startAddress.
    // Each instruction is split into 2 bytes (high byte, low byte) and occupies
    // 2 consecutive memory cells. Address increments by 2 per instruction.
    void load(const std::vector<int>& program, int startAddress = 0);

    // Store a value at address. Address 0x00 goes to the screen (memory-mapped I/O).
    void store(int address, int value);

    // Read a value from address. Address 0x00 returns the screen's last value.
    int read(int address) const;

    // Alias for read().
    int get(int address) const;

    // Clear every cell to 0 (screen is not cleared).
    void reset();

    int size() const;
};

#endif // MEMORY_H
