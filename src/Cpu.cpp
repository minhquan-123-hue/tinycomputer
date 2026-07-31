#include "../lib/Cpu.h"

Cpu::Cpu(Bus& bus)
    : bus(bus)
{
}

FetchedInstruction Cpu::fetch()
{
    uint8_t program_counter = registers.get_pc();

    FetchedInstruction instruction;

    instruction.opcode_byte = bus.read(program_counter);
    instruction.operand_byte = bus.read(program_counter + 1);

    registers.increment_pc();
    registers.increment_pc();

    return instruction;
}

Registers& Cpu::get_registers()
{
    return registers;
}