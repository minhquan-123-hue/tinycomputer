#ifndef CPU_H
#define CPU_H

#include <cstdint>

#include "../lib/Bus.h"
#include "../lib/Registers.h"

struct FetchedInstruction
{
    uint8_t opcode_byte;
    uint8_t operand_byte;
};

class Cpu
{
public:
    explicit Cpu(Bus& bus);

    FetchedInstruction fetch();

    Registers& get_registers();

private:
    Registers registers;
    Bus& bus;
};

#endif