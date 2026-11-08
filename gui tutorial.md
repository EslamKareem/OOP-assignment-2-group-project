# GUI Tutorial — Vole Machine Simulator

**Project:** CS213 OOP Assignment 2 — Vole Machine Simulator (Bonus GUI)  
**Team:** Eslam Karim, Omar Yasser, Mohammed Gherbawi, Kareem Adel  
**Instructor:** Dr. Mohammad El-Ramly, Cairo University (FCAI)  
**Framework:** Dear ImGui + SDL2 + OpenGL 3 (cross-platform: Windows / Linux)  
**Theme:** Nordic (polar-night dark background, snow text, frost accents)

---

## Overview

The GUI is a **frontend only** — it does not change any backend logic. It instantiates your `Machine` object and calls its public methods:
- `machine.loadProgram()` — loads a program into memory
- `machine.step()` — executes one instruction
- `machine.run()` — auto-executes until HALT
- `machine.reset()` — resets CPU and memory
- `machine.getMemory().write()` — manual memory store

The GUI reads state every frame (PC, registers, memory, screen output) and draws it on screen.

---

## 1. Build & Run

### Prerequisites
- SDL2 development libraries
- OpenGL development libraries
- CMake 3.10+
- g++ (C++17)

### Build Commands
```bash
cd "/home/eslam/Documents/Work space/OOP-assignment-2-group-project"
mkdir -p build
cd build
cmake ..
make
./vole_gui
```

### Troubleshooting Build
| Error | Fix |
|-------|-----|
| `"/home" does not contain CMakeLists.txt` | You're in the wrong directory. `cd` into the project folder first |
| `make: *** No targets specified` | Run `cmake ..` before `make` |
| `SDL2 not found` | Install SDL2 dev libraries (`sudo apt install libsdl2-dev`) |

---

## 2. GUI Layout (3 Panels)

The window has three equal side-by-side panels:

```
┌─────────────┬─────────────┬─────────────┐
│ Execution   │ Registers   │ Memory      │
│ (Left)      │ (CPU)       │ (Right)     │
├─────────────┼─────────────┼─────────────┤
│ • Counter   │ • Program   │ • Address   │
│ • Run/Stop  │   Counter   │ • Binary    │
│ • Load Prog │ • IR        │ • Hexadecimal│
│ • Screen    │ • Register  │ • ASCII     │
│ • Store     │   File      │             │
│ • Reset     │             │             │
│ • Exit      │             │             │
│ • Status    │             │             │
└─────────────┴─────────────┴─────────────┘
```

---

## 3. Panel Details

### Left Panel — Execution

| Element | What It Does |
|---------|-------------|
| **Counter** | Shows the current Program Counter (PC) value in hex |
| **Run** | Starts auto-execution (steps every 100ms until HALT). Button changes to "Pause" while running |
| **Stop** | Stops auto-execution |
| **Load Sample Program 1** | Loads Program 1 (sum 1+2+3+4+5 → `0x0F`) |
| **Load Sample Program 2** | Loads Program 2 (6 × 3 → `0x12`) |
| **Screen** | Displays ASCII output from memory address `0x00` (white text) |
| **Store in Memory** | Manually write values to memory |
| **Start Address** | Text field for the memory address to start writing |
| **Content** | Text field for hex/decimal values (space-separated) |
| **Store** | Writes the content values to memory starting at the address |
| **Reset** | Resets CPU, reloads last program, clears screen, Status → READY |
| **Exit** | Closes the GUI |
| **Status** | `READY` (green) or `HALTED` (red) |

### Middle Panel — Registers (CPU)

| Element | What It Shows |
|---------|--------------|
| **Program Counter** | Current PC value in hex |
| **Status badge** | HALTED (red) or RUNNING (green) |
| **Instruction Register** | Last fetched instruction: raw (hex), binary, opcode, r, s, t, xy fields |
| **Register File** | Table: Address (R0–RF) \| Binary \| Hexadecimal |

### Right Panel — Memory

| Element | What It Shows |
|---------|--------------|
| **Memory Grid** | Scrollable table of all 256 cells (0x00–0xFF) |
| **Columns** | Address \| Binary \| Hexadecimal \| ASCII |
| **Address 0x00** | Highlighted green — memory-mapped to Screen output device |

---

## 4. Step-by-Step Testing

### Test 1: Load & Run Program 1 (Sum 1→5)

1. Click **"Load Sample Program 1"** (left panel)
2. Click **"Run"** — auto-executes until HALT
3. **Expected:** Screen terminal shows `0x0F`, Status = `HALTED`, Register R0 = `0x0F`

### Test 2: Load & Run Program 2 (6 × 3)

1. Click **"Load Sample Program 2"**
2. Click **"Run"**
3. **Expected:** Screen shows `0x12` (18 decimal)

### Test 3: Step-by-Step Execution

1. Click **"Load Sample Program 3"** (loads `0x0A` → screen)
2. Click **"Run"** once → executes 1 instruction
3. Watch: PC advances `0x00` → `0x02`, R0 becomes `0x0A`
4. Click **"Run"** again → PC → `0x04`, Screen shows `0x0A`
5. Click **"Run"** again → Status = `HALTED`

### Test 4: Manual Memory Store

1. **Start Address:** `5`
2. **Content:** `42`
3. Click **"Store"**
4. **Expected:** Memory grid address `0x05` shows `2A` (42 in hex)

### Test 5: Reset

1. After running any program, click **"Reset"**
2. **Expected:** Status → `READY`, PC → `0x00`, screen clears
3. Click **"Run"** again — program executes from start (same result, deterministic)

### Test 6: Exit

1. Click **"Exit"** — window closes

---

## 5. Expected Results (All 10 Programs)

| Program | Operation | Screen Output |
|---------|-----------|---------------|
| P1 | Sum 1+2+3+4+5 | `0x0F` |
| P2 | 6 × 3 | `0x12` |
| P3 | Load immediate 0x0A | `0x0A` |
| P4 | 3 + 5 | `0x08` |
| P5 | OR 1 \| 2 | `0x03` |
| P6 | AND 3 & 1 | `0x01` |
| P7 | XOR 6 ^ 3 | `0x05` |
| P8 | Load immediate 0x0F | `0x0F` |
| P9 | 1 + 2 | `0x03` |
| P10 | 5 + 10 | `0x0F` |

> **Note:** Results are deterministic — running the same program multiple times always produces the same output.

---

## 6. Key Concepts

- **HALTED** = CPU executed a HALT instruction (`0xC`) and stopped. Click **Reset** to start again.
- **Address 0x00** = Memory-mapped to Screen. Any value stored here appears in the Screen terminal.
- **Green cell** in memory grid = address `0x00` (Screen output device).
- **Deterministic** = Same input always produces same output.

---

## 7. File Structure

```
OOP-assignment-2-group-project/
├── gui_main.cpp          # GUI entry point (frontend only)
├── CMakeLists.txt        # Build configuration
├── main.cpp              # Original console version (unchanged)
├── Makefile              # Original console Makefile (unchanged)
├── CPU.cpp/h             # CPU implementation (fixed to match diagram)
├── machine.cpp/h         # Machine orchestrator
├── Memory.cpp/h          # 256-byte RAM with MMIO at 0x00
├── Screen.cpp/h          # Screen output device
├── Register.cpp/h        # Single register (read/write)
├── RegisterFile.cpp/h    # 16 Register objects (R0-RF)
├── ALU.cpp/h             # ALU operations (bitOr, bitAnd, bitXor, etc.)
├── InstructionDecoder.cpp/h  # Decodes 16-bit instructions (+ decodeWord)
├── Programs.cpp/h        # 10 test programs (fixed encodings)
├── Opcode.h              # Opcode enum (JUMP → JUMP_EQ)
├── vendor/imgui/         # Dear ImGui library (vendored)
├── PLAN.md               # Implementation plan
└── build/                # Build output (generated)
```

---

## 8. Sending to Your Team

1. **Zip file:** `OOP-assignment-2-group-project.zip` (in parent directory)
2. **Build instructions:** Share the "Build & Run" section above
3. **Testing:** Have each team member run Tests 1–6 and verify the expected screen values match
4. **Obsidian:** Save this file as `gui tutorial.md` in your Obsidian vault

---

**Made by Islam Karim** \| **Cairo University — Faculty of Computers and Artificial Intelligence** \| **CS111**
