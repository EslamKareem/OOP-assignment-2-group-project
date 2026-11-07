#pragma once
#include "Screen.h"
#include <vector>
class Memory {
private:
  static const int SIZE = 256;
  std::vector<int> cells;
  Screen &screen;

public:
  explicit Memory(Screen &screenRef);
  ~Memory() = default;
  void load(const std::vector<int> &program, int startAddress = 0);
  void store(int address, int value);
  int read(int address) const;
  int get(int address) const;
  void reset();
  int size() const;
};
