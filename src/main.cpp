#include <iostream>
#include <iomanip>
#include "../lib/Bus.h"
#include "../lib/RAM.h"
#include "../lib/Registers.h"
#include "../lib/Cpu.h"
#include "../lib/Intructions.h"
#include "../lib/Alu.h"

int main()
{

    std::cout << "\n=== Step 11: Execute ===\n";

    Bus execution_bus;
    Cpu execution_cpu(execution_bus);

    execution_bus.write(0x00, OPCODE_LOAD_IMM);
    execution_bus.write(0x01, 0x05);
    execution_bus.write(0x02, OPCODE_MOV_A_B);
    execution_bus.write(0x03, 0x00);
    execution_bus.write(0x04, OPCODE_LOAD_IMM);
    execution_bus.write(0x05, 0x03);
    execution_bus.write(0x06, OPCODE_ADD);
    execution_bus.write(0x07, 0x00);
    execution_bus.write(0x08, OPCODE_STORE);
    execution_bus.write(0x09, 0x50);
    execution_bus.write(0x0A, OPCODE_HALT);
    execution_bus.write(0x0B, 0x00);

    execution_cpu.get_registers().set_pc(0x00);

    while (true)
    {
        FetchedInstruction fetched_instruction = execution_cpu.fetch();
        DecodedInstruction decoded_instruction = execution_cpu.decode(fetched_instruction);
        ExecuteResult execution_result = execution_cpu.execute(decoded_instruction);

        if (execution_result.is_halted)
        {
            break;
        }
    }

    std::cout << "Final A register: " << static_cast<int>(execution_cpu.get_registers().get_a()) << '\n';
    std::cout << "RAM[0x50]: " << static_cast<int>(execution_cpu.get_bus().read(0x50)) << '\n';

    Bus jump_bus;
    Cpu jump_cpu(jump_bus);

    jump_bus.write(0x00, OPCODE_LOAD_IMM);
    jump_bus.write(0x01, 0x05);
    jump_bus.write(0x02, OPCODE_JMP);
    jump_bus.write(0x03, 0x08);
    jump_bus.write(0x04, OPCODE_LOAD_IMM);
    jump_bus.write(0x05, 0x09);
    jump_bus.write(0x06, OPCODE_HALT);
    jump_bus.write(0x07, 0x00);
    jump_bus.write(0x08, OPCODE_HALT);
    jump_bus.write(0x09, 0x00);

    jump_cpu.get_registers().set_pc(0x00);

    while (true)
    {
        FetchedInstruction fetched_instruction = jump_cpu.fetch();
        DecodedInstruction decoded_instruction = jump_cpu.decode(fetched_instruction);
        ExecuteResult execution_result = jump_cpu.execute(decoded_instruction);

        if (execution_result.is_halted)
        {
            break;
        }
    }

    std::cout << "JMP test — A register (should be unchanged, confirming skip worked): "
              << static_cast<int>(jump_cpu.get_registers().get_a()) << '\n';

}

