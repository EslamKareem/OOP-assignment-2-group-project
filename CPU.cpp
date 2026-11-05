#include "CPU.h"

CPU::CPU(RegisterFile& registers, Memory& memory, ALU& alu, InstructionDecoder& decoder): registers(registers), memory(memory), alu(alu), decoder(decoder), programCounter(0), InstructionRegister(), halted(false) {}

void CPU::step(){}
void CPU::run(){}
void CPU::reset(){}
void CPU::halt(){}
bool CPU::isHalted() const{ return halted;}
int CPU::getProgramCounter() const{ return programCounter;}
void CPU::setProgramCounter(int address){}

RegisterFile& CPU::getRegisters(){ return registers;}
const RegisterFile& CPU::getRegisters() const { return registers;}
Memory& CPU::getMemory(){ return memory;}
const Memory& CPU::getMemory() const {return memory;}
ALU& CPU::getALU(){return alu}
const ALU& CPU::getALU() const { return alu;}