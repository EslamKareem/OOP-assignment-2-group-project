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
const std::optional<Instruction>& CPU::getInstructionRegister() const{ return InstructionRegister;}
void CPU::setProgramCounter(int address){
    programCounter = address & 0xff;
}

RegisterFile& CPU::getRegisters(){ return registers;}
const RegisterFile& CPU::getRegisters() const { return registers;}
Memory& CPU::getMemory(){ return memory;}
const Memory& CPU::getMemory() const {return memory;}
ALU& CPU::getALU(){return alu;}
const ALU& CPU::getALU() const { return alu;}

// fetch() — read 2 bytes (big-endian: high byte then low byte) from Memory at
// programCounter, combine into a 16-bit instruction, advance PC by 2, decode.
Instruction CPU::fetch(){
    uint8_t high = static_cast<uint8_t>(memory.read(programCounter));
    uint8_t low  = static_cast<uint8_t>(memory.read(programCounter + 1));
    programCounter += 2;
    return decoder.decode(high, low);
}

// execute() — decode the opcode and dispatch to the matching exec* method.
// Halts the machine on an invalid/unknown instruction.
void CPU::execute(const Instruction& i){
    if (!i.isValid()) {
        halt();
        return;
    }
    switch (i.getOpcode()){
        case Opcode::LOAD_MEM:  execLoadMem(i);  break;
        case Opcode::LOAD_IMM:  execLoadImm(i);  break;
        case Opcode::STORE:     execStore(i);    break;
        case Opcode::MOVE:      execMove(i);     break;
        case Opcode::ADD_INT:   execAddInt(i);   break;
        case Opcode::ADD_FLOAT: execAddFloat(i); break;
        case Opcode::OR_OP:     execOr(i);       break;
        case Opcode::AND_OP:    execAnd(i);      break;
        case Opcode::XOR_OP:    execXor(i);      break;
        case Opcode::ROTATE:    execRotate(i);   break;
        case Opcode::JUMP_EQ:      programCounter = i.getAddress() & 0xFF; break;
        case Opcode::HALT:      execHalt();      break;
        default:                halt();          break;
    }
}

void CPU::execJumpEq(const Instruction &i){
    // Conditional jump B: if R[r] != R[0], PC = XY
    if(registers.read(i.getR()) != registers.read(0)){
        programCounter = i.getAddress() & 0xff;
    }
}

void CPU::execLoadMem(const Instruction& i){
    // Load from memory address formed by s(hi 2 bits) : xy(lo 6 bits) into R[r]
    int address = (static_cast<int>(i.getS()) << 6) | static_cast<int>(i.getXY());
    registers.write(static_cast<int>(i.getR()), memory.read(address));
}

void CPU::execLoadImm(const Instruction& i){
    // Load immediate xy into R[r]
    registers.write(static_cast<int>(i.getR()), static_cast<uint8_t>(i.getXY()));
}

void CPU::execStore(const Instruction& i){
    // Store R[r] into memory address xy (address 0x00 is memory-mapped to the Screen)
    memory.write(static_cast<int>(i.getXY()), registers.read(i.getR()));
}

void CPU::execMove(const Instruction& i){
    // R[t] = R[r]
    registers.write(static_cast<int>(i.getT()), registers.read(i.getR()));
}

void CPU::execAddInt(const Instruction& i){
    // R[t] = R[r] + R[s]  (8-bit wrapping via ALU)
    int result = alu.addTwosComplement(registers.read(i.getR()), registers.read(i.getS()));
    registers.write(static_cast<int>(i.getT()), static_cast<uint8_t>(result));
}

void CPU::execAddFloat(const Instruction& i){
    // R[t] = R[r] + R[s]  (floating-point ALU op, same 8-bit wrapping for this machine)
    int result = alu.addFloat(registers.read(i.getR()), registers.read(i.getS()));
    registers.write(static_cast<int>(i.getT()), static_cast<uint8_t>(result));
}

void CPU::execOr(const Instruction& i){
    // R[t] = R[r] | R[s]
    registers.write(static_cast<int>(i.getT()), alu.bitOr(registers.read(i.getR()), registers.read(i.getS())));
}

void CPU::execAnd(const Instruction& i){
    // R[t] = R[r] & R[s]
    registers.write(static_cast<int>(i.getT()), alu.bitAnd(registers.read(i.getR()), registers.read(i.getS())));
}

void CPU::execXor(const Instruction& i){
    // R[t] = R[r] ^ R[s]
    registers.write(static_cast<int>(i.getT()), alu.bitXor(registers.read(i.getR()), registers.read(i.getS())));
}

void CPU::execRotate(const Instruction& i){
    // R[t] = rotateRight(R[t], xy)
    registers.write(static_cast<int>(i.getT()), alu.rotateRight(registers.read(i.getT()), static_cast<int>(i.getXY())));
}

void CPU::execHalt(){
    halt();
}