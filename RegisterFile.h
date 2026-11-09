#ifndef REGISTER_FILE_H
#define REGISTER_FILE_H

#include "Register.h"
#include <array>
#include <cstdint>
#include <iostream>
using namespace std;
class RegisterFile {
public:
  static const int NUM_REGISTERS = 16;

  RegisterFile();
  int read(int index) const;
  void write(int index, int value);
  void reset();
  string dump() const;

private:
  Register registers[NUM_REGISTERS];
};

#endif
