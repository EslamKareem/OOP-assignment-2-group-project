#pragma once
#include "Screen.h"
#include <vector>
#include <array>
using namespace std;
class Memory {
private:
  static const int SIZE = 256;
  array<int, SIZE> cells;
  Screen &screen;

  bool isScreenAddress(int address) const;

public:
  explicit Memory(Screen &screenRef);
  ~Memory() = default;

  void load(const std::vector<int> &program, int startAddress = 0);
  void write(int address, int value);
  int read(int address) const;
  void reset();
  string dump() const;
};
