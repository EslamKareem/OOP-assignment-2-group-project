#include "Memory.h"
#include "Programs.h"
#include "Screen.h"
#include <iomanip>
#include <iostream>
#include <vector>

int main() {

  Screen screen;
  Memory memory(screen);
  memory.store(0x00, 0x0F); // address 0x00 -> goes to screen
  memory.store(0x05, 0x42); // normal RAM cell
  memory.store(0x00, 0x12); // overwrite screen output

  std::cout << "--- Direct Memory <-> Screen test ---" << std::endl;
  std::cout << "Screen: ";
  screen.display(); // expect 0x12
  std::cout << "RAM[0x05] = 0x" << std::hex << std::uppercase << std::setw(2)
            << std::setfill('0') << memory.read(0x05) << std::dec
            << "   (expect 0x42)" << std::endl;
  std::cout << "RAM[0x00] = 0x" << std::hex << std::uppercase << std::setw(2)
            << std::setfill('0') << memory.read(0x00) << std::dec
            << "   (expect 0x12, reads from screen)" << std::endl;

  return 0;
}
