#ifndef PROGRAMS_H
#define PROGRAMS_H
#include <vector>

class Programs {
public:
  // Program 1: sum 1+2+3+4+5 = 0x0F
  //   2001 2102 2203 2304 2405 5501 5552 5553 5554 3500 C000
  static std::vector<int> program1();

  // Program 2: 6 x 3 = 0x12 (18 decimal) using addition
  //   2006 5100 5210 3200 C000
  static std::vector<int> program2();

  // Program 3: load immediate 0x0A and display on screen
  //   200A 3100 C000  -> Screen = 0x0A
  static std::vector<int> program3();

  // Program 4: add 3 + 5 = 8, display 0x08
  //   2003 2105 5201 3200 C000
  static std::vector<int> program4();

  // Program 5: OR 1 | 2 = 3, display 0x03
  //   2001 2102 5701 3700 C000
  static std::vector<int> program5();

  // Program 6: AND 3 & 1 = 1, display 0x01
  //   2003 2101 5801 3800 C000
  static std::vector<int> program6();

  // Program 7: XOR 6 ^ 3 = 5, display 0x05
  //   2006 2103 5901 3900 C000
  static std::vector<int> program7();

  // Program 8: load immediate 0x0F and display
  //   200F 3100 C000  -> Screen = 0x0F
  static std::vector<int> program8();

  // Program 9: add 1 + 2 = 3, display 0x03
  //   2001 2102 5301 3300 C000
  static std::vector<int> program9();

  // Program 10: add 5 + 10 = 15, display 0x0F
  //   2005 210A 5401 3400 C000
  static std::vector<int> program10();

  // Return all 10 programs as a vector of vectors.
  static std::vector<std::vector<int>> allPrograms();
};

#endif // PROGRAMS_H
