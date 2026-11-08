#include "RegisterFile.h"
#include <ios>
#include <sstream>
#include <iomanip>
using namespace std;

RegisterFile::RegisterFile() {
    reset();
}

uint8_t RegisterFile::read(int index) const {
    if (index >= 0 && index < NUM_REGISTERS) {
        return static_cast<uint8_t>(registers[index]);
    }
    return 0;
}

void RegisterFile::write(int index, uint8_t value) {
    if (index >= 0 && index < NUM_REGISTERS) {
        registers[index] = value;
    }
}

void RegisterFile::reset() {
    fill(begin(registers), end(registers), 0);
}

string RegisterFile::dump() const{
  ostringstream oss ;
    for(int i = 0; i < NUM_REGISTERS; i++){
      oss << "R"<< setw(2) << setfill('0') << dec << i << "=" << "0x"<< hex << uppercase << setw(2)<< setfill('0')<< registers[i] << " ";
      if (i % 4 == 3){
        oss << "\n";
      }
    }
    return oss.str();
}

