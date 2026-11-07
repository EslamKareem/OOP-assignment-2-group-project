#ifndef SCREEN_H
#define SCREEN_H

#include <iomanip>
#include <iostream>
class Screen {
private:
  int lastValue;

public:
  Screen();
  ~Screen() = default;
  void write(int value);
  void display() const;
  int getLastValue() const;
};
#endif
