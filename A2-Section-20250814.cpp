#include <iostream>
#include <iomanip>
#include <vector>
#include "machine.h"
#include "Programs.h"

// Application entry point for the Vole machine simulator.
// Requirement 6: Application file named A2-YourSection-YourIDs.cpp
// Replace "Section" with your actual section number before submission.

int main() {
    Machine machine;

    std::cout << "=== Vole Machine Simulator - CS213 Assignment 2 ===" << std::endl;
    std::cout << "Team Member: Eslam Karim (20250814)" << std::endl;
    std::cout << "Memory: 256 cells | Screen: memory-mapped at address 0x00" << std::endl;
    std::cout << std::endl;

    // ------------------------------------------------------------
    // Part 1: Direct test of Memory <-> Screen memory-mapped I/O.
    // Proves Eslam's Memory + Screen work without needing the CPU.
    // ------------------------------------------------------------
    {
        Screen screen;
        Memory memory(screen);

        memory.store(0x00, 0x0F);   // address 0x00 -> goes to screen
        memory.store(0x05, 0x42);   // normal RAM cell
        memory.store(0x00, 0x12);   // overwrite screen output

        std::cout << "--- Direct Memory <-> Screen test ---" << std::endl;
        std::cout << "Screen: ";
        screen.display();                       // expect 0x12
        std::cout << "RAM[0x05] = 0x"
                  << std::hex << std::uppercase << std::setw(2)
                  << std::setfill('0') << memory.read(0x05)
                  << std::dec << "   (expect 0x42)" << std::endl;
        std::cout << "RAM[0x00] = 0x"
                  << std::hex << std::uppercase << std::setw(2)
                  << std::setfill('0') << memory.read(0x00)
                  << std::dec << "   (expect 0x12, reads from screen)" << std::endl;
    }

    std::cout << std::endl;

    // ------------------------------------------------------------
    // Part 2: Run all 10 sample programs through the Machine.
    // NOTE: CPU::execute is currently a stub (teammates' work), so
    // machine.run() does not execute instructions yet. Once the CPU
    // is implemented, each program should display its expected result.
    // ------------------------------------------------------------
    std::cout << "--- Running 10 sample programs ---" << std::endl;
    std::cout << std::endl;

    auto allPrograms = Programs::allPrograms();
    const char* expected[] = {
        "0x0F", "0x12", "0x0A", "0x08", "0x03",
        "0x01", "0x05", "0x0F", "0x03", "0x0F"
    };

    for (size_t i = 0; i < allPrograms.size(); ++i) {
        std::cout << "Program " << (i + 1) << " (expect " << expected[i] << "): ";
        machine.loadProgram(allPrograms[i]);
        machine.run();
        std::cout << "Screen: ";
        machine.getscreen().display();
        machine.reset();
    }

    std::cout << std::endl;
    std::cout << "=== All 10 programs loaded. ===" << std::endl;
    std::cout << "Note: Screens show 0x00 until CPU::execute is implemented by teammates." << std::endl;

    return 0;
}
