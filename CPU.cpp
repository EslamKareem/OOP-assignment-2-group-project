#include "CPU.h"

CPU::CPU(RegisterFile& registers, Memory& memory, ALU& alu, InstructionDecoder& decoder): registers(registers), memory(memory), alu(alu), decoder(decoder), programCounter(0), InstructionRegister(), halted(false) {}

void CPU::step(){
    if (halted) return;
    Instruction ins = fetch();
    InstructionRegister = ins;
    execute(ins);
}
void CPU::run(){
    while (!halted){
        step();
    }
}
void CPU::reset(){
    programCounter = 0;
    InstructionRegister.reset();
    halted = false ;
    registers.reset();
}
void CPU::halt(){
    halted = true ;
}

bool CPU::isHalted() const{ return halted;}
int CPU::getProgramCounter() const{ return programCounter;}
void CPU::setProgramCounter(int address){
    programCounter = address & 0xff;
}

RegisterFile& CPU::getRegisters(){ return registers;}
const RegisterFile& CPU::getRegisters() const { return registers;}
Memory& CPU::getMemory(){ return memory;}
const Memory& CPU::getMemory() const {return memory;}
ALU& CPU::getALU(){return alu;}
const ALU& CPU::getALU() const { return alu;}

// TODO(Teammates): Implement fetch() — read 2 bytes from memory at programCounter,
// combine into 16-bit instruction, increment PC, return Instruction.
Instruction CPU::fetch(){
    return Instruction(Opcode::HALT, 0, 0, 0, 0, 0xC000, true);
}

// TODO(Teammates): Implement execute() — decode opcode and call appropriate exec* method.
void CPU::execute(const Instruction& i){
    (void)i;  // placeholder
    if (i.getOpcode() == Opcode::HALT) {
        halt();
    }
}

void CPU::execJumpEq(const Instruction &i){
    if(registers.read(i.getR()) == registers.read(0)){
        programCounter = i.getAddress() & 0xff;
    }
}