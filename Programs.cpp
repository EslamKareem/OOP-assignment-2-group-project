#include "Programs.h"

// Instruction encoding format (16 bits, 2 bytes):
//   High byte:  opcode(4 bits) | r(2 bits) | s(2 bits)
//   Low byte:   t(2 bits) | xy(6 bits)
// Registers addressable by r/s/t fields: R0-R3 (2-bit fields)

std::vector<int> Programs::program1() {
  // Sum 1+2+3+4+5 = 15 (0x0F), store to screen
  // R0=1, R1=2, R0=R0+R1, R1=3, R0=R0+R1, R1=4, R0=R0+R1, R1=5, R0=R0+R1, STORE R0->0x00, HALT
  return {0x2001, 0x2402, 0x5100,
          0x2403, 0x5100,
          0x2404, 0x5100,
          0x2405, 0x5100,
          0x3000, 0xC000};
}

std::vector<int> Programs::program2() {
  // 6 x 3 = 18 (0x12), store to screen
  // R0=6, R1=0, R1=R1+R0 x3, STORE R1->0x00, HALT
  return {0x2006, 0x2400,
          0x5440, 0x5440, 0x5440,
          0x3400, 0xC000};
}

std::vector<int> Programs::program3() { return {0x200A, 0x3000, 0xC000}; }

std::vector<int> Programs::program4() {
  // 3 + 5 = 8 (0x08), store to screen
  return {0x2003, 0x2405, 0x5100, 0x3000, 0xC000};
}

std::vector<int> Programs::program5() {
  // OR 1 | 2 = 3 (0x03), store to screen
  return {0x2001, 0x2402, 0x7100, 0x3000, 0xC000};
}

std::vector<int> Programs::program6() {
  // AND 3 & 1 = 1 (0x01), store to screen
  return {0x2003, 0x2401, 0x8100, 0x3000, 0xC000};
}

std::vector<int> Programs::program7() {
  // XOR 6 ^ 3 = 5 (0x05), store to screen
  return {0x2006, 0x2403, 0x9100, 0x3000, 0xC000};
}

std::vector<int> Programs::program8() { return {0x200F, 0x3000, 0xC000}; }

std::vector<int> Programs::program9() {
  // 1 + 2 = 3 (0x03), store to screen
  return {0x2001, 0x2402, 0x5100, 0x3000, 0xC000};
}

std::vector<int> Programs::program10() {
  // 5 + 10 = 15 (0x0F), store to screen
  return {0x2005, 0x240A, 0x5100, 0x3000, 0xC000};
}

std::vector<std::vector<int>> Programs::allPrograms() {
  return {program1(), program2(), program3(), program4(), program5(),
          program6(), program7(), program8(), program9(), program10()};
}
