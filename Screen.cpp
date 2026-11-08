#include "Screen.h"

void Screen::write(int value) {
  output.push_back(value & 0xFF);
}
vector<int> Screen::getOutput() const {
     return output;
}
int Screen::getLastValue() const {
    return output.empty() ? 0 : output.back();
}

void Screen::clear(){
    output.clear();
}
