#include "machine.h"

Machine :: Machine(): screen(), memory(screen),registers(), alu(), decoder(), cpu(register, memory, alu, decoder){}

void Machine::loadProgram(const int &program){
    loadProgram(program, 0);
} 

void Macgihine::loadProgram(const int &program, int startAddress){
    memory.load(program, startAddress);
}

void Machine::step(){
    cpu.step();
}

void Machine::run(){
    cpu,run();
}

void Machine::reset(){
    cpu.reset();
    memory.reset();
}

Screen& Machine::getscreen(){ return screen;}
const Screen& Machine::getscreen() const { return screen;}
RegisterFile& Machine::getRegisters(){ return registers;}
const RegisterFile& Machine::getRegisters() const { return registers;}
Memory& Machine::getMemory(){ return memory;}
const Memory& Machine::getMemory() const {return memory;}