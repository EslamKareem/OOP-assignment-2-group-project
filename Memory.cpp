#include "Memory.h"
#include <iomanip>
#include <ios>
#include <sstream>

Memory::Memory(Screen &screenRef) : screen(screenRef), cells{} {}

bool Memory::isScreenAddress(int address) const{
   int addr = address & 0xff;
   return addr == 0x00 || addr == 0xFF;
}

void Memory::load(const std::vector<int> &program, int startAddress) {
  for (size_t i = 0; i < program.size(); ++i) {
    int addr =
        startAddress + static_cast<int>(i * 2); // Each instruction is 2 bytes
    if (addr >= 0 && (addr + 1) < SIZE) {
      cells[addr] = (program[i] >> 8) & 0xFF; // the high byte
      cells[addr + 1] = program[i] & 0xFF;    // the low byte
    }
  }
}

void Memory::write(int address, int value) {
   int addr = address & 0xFF;
   if (isScreenAddress(addr)){
       screen.write(value & 0xFF);
       return;
   }
   cells[addr] = value & 0xFF;
}

int Memory::read(int address) const {
    return cells[address & 0xFF];
}


void Memory::reset() { 
   cells.fill(0);
 }

string Memory::dump() const{
  ostringstream oss ;
    for(int i = 0; i < SIZE; i++){
      if (i% 8 == 0){
         oss << setw(2) << setfill('0') << hex << uppercase << i << ":"; 
      }
      oss << setw(2) << setfill('0') << hex << uppercase << cells[i] << " ";
      if (i % 8 == 7){
        oss << "\n";
      }
    }
    return oss.str();
}
