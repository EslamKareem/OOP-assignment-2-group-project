#pragma once

#include <iomanip>
#include <iostream>
#include <vector>
using namespace std;
class Screen {
private:
  vector<int> output;

public:
  Screen();
  ~Screen() = default;

  void write(int value);
  vector<int> getOutput() const;
  int getLastValue() const;
  void clear();
};
