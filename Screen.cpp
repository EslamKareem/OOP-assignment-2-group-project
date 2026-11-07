#include "Screen.h"
Screen::Screen() : lastValue(0) {}
void Screen::write(int value) {
  lastValue = value & 0xFF; // keep only the low byte
}
void Screen::display() const {
  std::cout << "0x" << std::hex << std::uppercase << std::setw(2)
            << std::setfill('0') << (lastValue & 0xFF) << std::dec << std::endl;
}
int Screen::getLastValue() const { return lastValue; }
