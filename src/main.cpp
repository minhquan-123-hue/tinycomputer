#include <iostream>
#include <iomanip>
#include "../lib/Bus.h"
#include "../lib/RAM.h"
#include "../lib/Registers.h"
#include "../lib/Cpu.h"
#include "../lib/Intructions.h"

int main()
{
    Bus bus;
    
    bus.write(0x00, OPCODE_LOAD);
    bus.write(0x01, 0x50);
    
    bus.write(0x02, OPCODE_HALT);
    bus.write(0x03, 0x00);
    
    Cpu cpu(bus);
    
    std::cout
        << "PC before fetch: "
        << static_cast<int>(cpu.get_registers().get_pc())
        << '\n';
    
    FetchedInstruction instruction = cpu.fetch();
    
    std::cout
        << "Fetched opcode: "
        << static_cast<int>(instruction.opcode_byte)
        << ", operand: "
        << static_cast<int>(instruction.operand_byte)
        << '\n';
    
    std::cout
        << "PC after fetch: "
        << static_cast<int>(cpu.get_registers().get_pc())
        << '\n';
    
    instruction = cpu.fetch();
    
    std::cout
        << "Fetched opcode: "
        << static_cast<int>(instruction.opcode_byte)
        << ", operand: "
        << static_cast<int>(instruction.operand_byte)
        << '\n';
    
    std::cout
        << "PC after fetch: "
        << static_cast<int>(cpu.get_registers().get_pc())
        << '\n';
}

