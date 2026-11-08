# Vole Machine GUI - Implementation Plan (COMPLETE)

## Step 1: Backend Sanity Check — aligned with PlantUML diagram (DONE)

Fixed all discrepancies vs the diagram:

| File | Fix | Diagram alignment |
|------|-----|-------------------|
| `Opcode.h` | Renamed `JUMP` → `JUMP_EQ` | Matches `JUMP_EQ = 0xB` |
| `ALU.h` | `addTowscomplement` → `addTwosComplement`, `bitwiseAnd` → `bitAnd`, `bitwiseOr` → `bitOr`, added `bitXor`, made `toFloat`/`fromFloat` private | Matches diagram method names/signatures |
| `ALU.cpp` | Updated implementations, added `bitXor`, `toFloat`, `fromFloat` | Matches diagram |
| `CPU.cpp` | `execJumpEq`: changed `==` → `!=` (conditional jump: if R[r] != R[0], PC = XY), updated all ALU calls to new names, `Opcode::JUMP` → `Opcode::JUMP_EQ` | Matches diagram behavior |
| `CPU.h` | Internal methods (`fetch`, `execute`, `exec*`) already `private` | Matches diagram |
| `InstructionDecoder.h/cpp` | Added `decodeWord(uint16_t word)` | Matches diagram |
| `Register.h/cpp` | `Getvalue`/`Setvalue` → `read()`/`write()`, `read()` is `const` | Matches diagram |
| `RegisterFile.h/cpp` | Changed `int[16]` → `Register[16]`, uses `Register::read()`/`write()` | Matches diagram `-registers: Register[16]` |
| `gui_main.cpp` | `Opcode::JUMP` → `Opcode::JUMP_EQ` | Matches diagram |
| `CMakeLists.txt` | Added `Register.cpp` to sources | Builds all diagram classes |

Console `main.cpp` compiles cleanly with no errors.

## Step 2: GUI (DONE — Nordic theme, matches diagram layout)

- `gui_main.cpp`: ImGui + SDL2 + OpenGL3, Nordic theme
- Three panels matching diagram concepts: Execution / Registers (CPU) / Memory
- Load Program 1/2 buttons, Run/Stop, Reset, Exit
- Manual Store in Memory (Start Address + Content)
- Screen output (white text per Image 2)
- Register file table: Address \| Binary \| Hexadecimal (R0–RF)
- Memory grid: Address \| Binary \| Hexadecimal \| ASCII, 0x00 highlighted green
- Footer: "Made by Islam Karim | Cairo University — FCAI | CS111"

## Step 3: Build (DONE)

- `CMakeLists.txt` links all backend .cpp + ImGui + SDL2 + OpenGL
- `mkdir build && cd build && cmake .. && make && ./vole_gui`
- Verified: builds and runs
