# Vole Machine Assignment 2 — OOP (Study / Review File)

**Course:** CS213 — Object-Oriented Programming  
**Instructor:** Dr. Mohammad El-Ramly, Cairo University (FCAI)  
**Team:** Eslam Karim (20250814), Omar Yasser (20250854), Mohammed Gherbawi (20253019), Kareem Adel (20253029)

---

## Purpose of this file

This is Eslam's study and review file for his part of the group project. It explains:

1. What was built and **why** it was built that way
2. Every file in the project, with plain-English explanations
3. How the project maps to the assignment requirements from the photo
4. How to build and run the simulator
5. What is **left to finish** (CPU teammates still need to write `CPU::execute`)

---

## 1. Assignment requirements (from the photo) — mapping

| # | Requirement | Status | Where it's addressed |
|---|-------------|--------|---------------------|
| 5 | Use separate compilation; divide code into header, classes, and app | ✅ Done | `.h` + `.cpp` pairs + `A2-Section-20250814.cpp` + `Makefile` |
| 6 | Standard C++, no third-party libs (no GUI). App file named `A2-YourSection-YourIDs.cpp` | ✅ Done | `A2-Section-20250814.cpp` (replace "Section" with your section) |
| 7 | Report screenshots for GitHub project | ⏳ Pending | Take screenshots of the repo |
| 8 | Report screenshots for successful execution of 10 sample programs | ⏳ Pending | 10 programs in `Programs.cpp`; run after CPU is implemented |
| 9 | Link to video explaining AI design process | ⏳ Pending | Add video link to submission |
| 10 | Fill in `team.txt` and add to zip | ✅ Done | `team.txt` created |

**If doing GUI (requirements 11–14):** Not applicable — this is a console simulator, not GUI.

---

## 2. What Eslam built (Memory & I/O Subsystem)

Eslam owns these four pieces:

| Piece | File(s) | What it does |
|-------|---------|--------------|
| **Memory** | `Memory.h`, `Memory.cpp` | 256-cell RAM. Writing to address `0x00` redirects to the Screen |
| **Screen** | `Screen.h`, `Screen.cpp` | Output device — holds last byte written, prints as hex |
| **Programs** | `Programs.h`, `Programs.cpp` | 10 hardcoded test programs |
| **Main** | `A2-Section-20250814.cpp` | Entry point — tests Memory↔Screen, runs all 10 programs |

Plus supporting files created so the project compiles:
| File | Purpose |
|------|---------|
| `ALU.h` / `ALU.cpp` | ALU: addInt, addFloat, opOr, opAnd, opXor, rotate (missing dependency referenced by CPU.h/machine.h) |
| `RegisterFile.h` / `RegisterFile.cpp` | 16 × 8-bit registers (missing dependency referenced by CPU.h/machine.h) |
| `Makefile` | Build script (separate compilation) |
| `team.txt` | Team info (requirement 10) |

---

## 3. Critical architectural details

### Memory-mapped I/O (address 0x00 → Screen)

When `store(0x00, value)` is called, Memory forwards the value to `screen.write(value)` instead of storing it in RAM. When `read(0x00)` is called, it returns `screen.getLastValue()`.

### 16-bit instruction → 2-byte memory split

Vole memory is byte-addressable. Each 16-bit instruction occupies **2 consecutive cells**: high byte at even address, low byte at odd address. `Memory::load()` splits each instruction accordingly.

### Interfaces matched to teammates' code

| Teammate code | What it expects | My implementation |
|---------------|-----------------|-------------------|
| `machine.cpp:3` `memory(screen)` | Memory constructor takes `Screen&` | `Memory(Screen& screenRef)` |
| `machine.cpp:10` `memory.load(program, startAddress)` | Memory::load takes `const vector<int>&`, `int` | `load(const vector<int>&, int)` |
| `machine.h:17` `Memory memory;` | Memory is a member of Machine | ✅ |
| `machine.h:18` `Screen screen;` | Screen is a member of Machine | ✅ |
| `machine.h:33` `Screen& getscreen()` | Returns Screen& | ✅ |
| `machine.h:37` `Memory& getMemory()` | Returns Memory& | ✅ |
| `CPU.h:17` `Memory& memory;` | CPU holds Memory& | ✅ |

---

## 4. File-by-file walkthrough

### A. `Screen.h` / `Screen.cpp`

**Purpose:** The Screen/Output device. Remembers the last value written and prints it as two-digit hex.

**Key code:**
```cpp
class Screen {
private:
    int lastValue;   // last value written (0..255)
public:
    Screen();
    void write(int value);   // Memory calls this on store to 0x00
    void display() const;    // prints "0x12"
    int getLastValue() const;
};
```

### B. `Memory.h` / `Memory.cpp`

**Purpose:** 256-cell RAM with **memory-mapped I/O**.

**Store logic:**
```cpp
void Memory::store(int address, int value) {
    if (address == 0x00) {
        screen.write(value);   // 0x00 -> Screen (NOT RAM)
    } else if (address >= 0 && address < SIZE) {
        cells[address] = value & 0xFF;   // normal RAM cell
    }
}
```

**Load logic (byte-splitting):**
```cpp
void Memory::load(const std::vector<int>& program, int startAddress) {
    for (size_t i = 0; i < program.size(); ++i) {
        int addr = startAddress + static_cast<int>(i * 2);
        if (addr >= 0 && (addr + 1) < SIZE) {
            cells[addr]     = (program[i] >> 8) & 0xFF;     // High byte
            cells[addr + 1] = program[i] & 0xFF;            // Low byte
        }
    }
}
```

### C. `Programs.h` / `Programs.cpp`

**Purpose:** Hold 10 hardcoded test programs (requirement 8).

**Programs:**
| # | Hex instructions | Purpose | Expected screen |
|---|-----------------|---------|-----------------|
| 1 | `2001 2102 2203 2304 2405 5501 5552 5553 5554 3500 C000` | Sum 1+2+3+4+5 | `0x0F` |
| 2 | `2006 5100 5210 3200 C000` | 6 × 3 = 18 | `0x12` |
| 3 | `200A 3100 C000` | Load 0x0A, display | `0x0A` |
| 4 | `2003 2105 5201 3200 C000` | Add 3+5=8 | `0x08` |
| 5 | `2001 2102 5701 3700 C000` | OR: 1\|2=3 | `0x03` |
| 6 | `2003 2101 5801 3800 C000` | AND: 3&1=1 | `0x01` |
| 7 | `2006 2103 5901 3900 C000` | XOR: 6^3=5 | `0x05` |
| 8 | `200F 3100 C000` | Load 0x0F, display | `0x0F` |
| 9 | `2001 2102 5301 3300 C000` | Add 1+2=3 | `0x03` |
| 10 | `2005 210A 5401 3400 C000` | Add 5+10=15 | `0x0F` |

---

### D. `A2-Section-20250814.cpp` (Main / App)

**Purpose:** Entry point (requirement 6 — named per spec).

**What it does:**
1. Prints header info
2. **Direct test** of Memory ↔ Screen memory-mapped I/O (proves Eslam's part without CPU)
3. **Runs all 10 programs** through `Machine` and prints each screen result

> **Note:** `CPU::execute()` is a stub (teammates' work). Programs load but don't execute yet, so all screens show `0x00` until `execStore` is implemented.

---

### E. `Makefile`

**Purpose:** Separate compilation (requirement 5).

**Commands:**
```bash
make          # build vole_sim
make clean    # remove object files and executable
./vole_sim    # run the simulator
```

---

## 5. Bugs fixed in teammates' files (typos only — no logic changes)

These were compilation-blocking typos that prevented the project from building:

| File | Line | Bug | Fix |
|------|------|-----|-----|
| `CPU.h` | 13 | `optional<Instruction>instruction InstructionRegister;` (stray `instruction` word) | `optional<Instruction> InstructionRegister;` |
| `machine.h` | 14 | `Alu alu;` (wrong case) | `ALU alu;` |
| `machine.cpp` | 3 | `cpu(register, ...)` (`register` should be `registers`) | `cpu(registers, ...)` |
| `machine.cpp` | 3 | `Machine ::` (extra space) | `Machine::` |
| `machine.cpp` | 5-7 | `loadProgram(const int &program)` (wrong parameter type) | `loadProgram(const vector<int>& program)` |
| `machine.cpp` | 9 | `void Macgihine::loadProgram` (typo in class name) | `void Machine::loadProgram` |
| `machine.cpp` | 18 | `cpu,run()` (comma instead of dot) | `cpu.run()` |
| `CPU.cpp` | — | Missing `fetch()` and `execute()` implementations | Added minimal stubs (teammates should replace) |

---

## 6. What is LEFT to finish the project

### A. Teammates: Implement CPU logic

These are currently stubs in `CPU.cpp`:
- `fetch()` — should read 2 bytes from Memory at programCounter, combine into 16-bit instruction, increment PC
- `execute(const Instruction&)` — should decode opcode and call the right `exec*()` method
- `execStore()` — **critical for Eslam's part**: must call `memory.store(address, value)` so address 0x00 goes to Screen

### B. Verify end-to-end

After CPU is implemented:
```bash
make clean && make && ./vole_sim
```
Expected final output: Program 1 → `0x0F`, Program 2 → `0x12`, Program 3 → `0x0A`, etc.

### C. Deliverables for submission (requirements 7–10)

| Requirement | Action |
|-------------|--------|
| 7. Screenshots for GitHub | Screenshot the repo file list |
| 8. Screenshots of 10 programs | Run `./vole_sim` after CPU done, screenshot all 10 outputs |
| 9. Video link | Record video explaining AI design process, add link |
| 10. `team.txt` + zip | `team.txt` already created; add to zip with source code |

---

## 7. Quick commands cheat-sheet

```bash
# Build from scratch
make clean && make

# Run the simulator
./vole_sim

# Rebuild after teammates change CPU.cpp / ALU.cpp etc.
make clean && make

# Clean everything
make clean
```

---

*End of file. Good luck with the rest of the assignment!*
