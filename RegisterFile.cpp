#include "RegisterFile.h"
#include <ios>
#include <sstream>
#include <iomanip>
using namespace std;

RegisterFile::RegisterFile() {
    reset();
}

int RegisterFile::read(int index) const {
    if (index >= 0 && index < NUM_REGISTERS) {
        return registers[index].read();
    }
    return 0;
}

void RegisterFile::write(int index, int value) {
    if (index >= 0 && index < NUM_REGISTERS) {
        registers[index].write(value);
    }
}

void RegisterFile::reset() {
    for (int i = 0; i < NUM_REGISTERS; i++) {
        registers[i].write(0);
    }
}

string RegisterFile::dump() const{
  ostringstream oss ;
    for(int i = 0; i < NUM_REGISTERS; i++){
      oss << "R"<< setw(2) << setfill('0') << dec << i << "=" << "0x"<< hex << uppercase << setw(2)<< setfill('0')<< registers[i].read() << " ";
      if (i % 4 == 3){
        oss << "\n";
      }
    }
    return oss.str();
}

