#include <vector>
#include "CPU.h"
#include "ALU.h"
#include "InstructionDecoder.h"
#include "RegisterFile.h"
#include "Memory.h"
#include "Screen.h"
using namespace std;

class Machine{
private:
        CPU cpu;
        Alu alu;
        InstructionDecoder decoder;
        RegisterFile register;
        Memory memory;
        Screen screen;
public:
        Machine();
        ~Machine() = default;

        Machine(const Machine&) = delete;
        Machine& operator=(const Machine&) = delete;

        void loadProgram(const vector<int>& program);
        void loadProgram(const vector<int>& program, int startAddress);

        void run();
        void step();
        void reset();

        Screen& getscreen();
        const Screen& getscreen() const ;
        RegisterFile& getRegisters();
        const RegisterFile& getRegisters() const;
        Memory& getMemory();
        const Memory& getMemory() const;
};
