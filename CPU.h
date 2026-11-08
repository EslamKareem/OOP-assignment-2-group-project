#pragma once
#include <optional>
#include "ALU.h"
#include "InstructionDecoder.h"
#include "RegisterFile.h"
#include "Memory.h"
#include "Instruction.h"
using namespace std;

class CPU{
private:
        int programCounter;
        optional<Instruction> InstructionRegister;
        bool halted;

        RegisterFile& registers;
        Memory& memory;
        ALU& alu;
        InstructionDecoder& decoder;

        Instruction fetch();
        void execute(const Instruction& i);
        void execLoadMem(const Instruction& i);
        void execLoadImm(const Instruction& i);
        void execStore(const Instruction& i);
        void execMove(const Instruction& i);
        void execAddInt(const Instruction& i);
        void execAddFloat(const Instruction& i);
        void execOr(const Instruction& i);
        void execAnd(const Instruction& i);
        void execXor(const Instruction& i);
        void execRotate(const Instruction& i);
        void execJumpEq(const Instruction& i);
        void execHalt();
public:
        CPU(RegisterFile& registers, Memory& memory, ALU& alu, InstructionDecoder& decoder);
        ~CPU() = default;

        CPU(const CPU&) = delete;
        CPU& operator=(const CPU&) = delete;

        void step();
        void run();
        void reset();
        void halt();
        bool isHalted() const;
        int getProgramCounter() const;
        void setProgramCounter(int address);

        // Instruction Register access (needed to observe the last executed instruction)
        const std::optional<Instruction>& getInstructionRegister() const;

        RegisterFile& getRegisters();
        const RegisterFile& getRegisters() const;
        Memory& getMemory();
        const Memory& getMemory() const;
        ALU& getALU();
        const ALU& getALU() const;
};
