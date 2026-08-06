#include <iostream>
#include "../lib/Bus.h"
#include "../lib/RAM.h"
#include "../lib/Registers.h"
#include "../lib/Cpu.h"
#include "../lib/Intructions.h"
#include "../lib/Compiler.h"

void run_one_plus_one_demo()
{
    Bus bus;
    Cpu cpu(bus);

    bus.write(0x00, OPCODE_LOAD_IMM); bus.write(0x01, 0x01); // A = 1
    bus.write(0x02, OPCODE_MOV_A_B);  bus.write(0x03, 0x00); // B = 1
    bus.write(0x04, OPCODE_ADD);      bus.write(0x05, 0x00); // A = A + B = 2
    bus.write(0x06, OPCODE_STORE);    bus.write(0x07, 0x60); // RAM[0x60] = A (save result temporarily)
    bus.write(0x08, OPCODE_LOAD_IMM); bus.write(0x09, 0x01); // A = 0x01
    bus.write(0x0A, OPCODE_STORE);    bus.write(0x0B, 0xF0); // SSD address low = 0x01
    bus.write(0x0C, OPCODE_LOAD_IMM); bus.write(0x0D, 0x00); // A = 0x00
    bus.write(0x0E, OPCODE_STORE);    bus.write(0x0F, 0xF1); // SSD address high = 0x00
    bus.write(0x10, OPCODE_LOAD);     bus.write(0x11, 0x60); // A = RAM[0x60] = 2
    bus.write(0x12, OPCODE_STORE);    bus.write(0x13, 0xF3); // SSD DATA_WRITE = 2
    bus.write(0x14, OPCODE_LOAD_IMM); bus.write(0x15, 0x30); // A = '0' (ASCII 48)
    bus.write(0x16, OPCODE_MOV_A_B);  bus.write(0x17, 0x00); // B = 48
    bus.write(0x18, OPCODE_LOAD);     bus.write(0x19, 0x60); // A = RAM[0x60] = 2
    bus.write(0x1A, OPCODE_ADD);      bus.write(0x1B, 0x00); // A = 2 + 48 = '2'
    bus.write(0x1C, OPCODE_STORE);    bus.write(0x1D, 0xE2); // OUTPUT = '2'
    bus.write(0x1E, OPCODE_HALT);     bus.write(0x1F, 0x00); // HALT

    cpu.get_registers().set_pc(0x00);
    cpu.run();

    std::cout << "Final A register (ASCII '2'): " << static_cast<int>(cpu.get_registers().get_a()) << '\n';
    std::cout << "RAM[0x60] (raw result): " << static_cast<int>(cpu.get_bus().read(0x60)) << '\n';

    bus.write(0xF0, 0x01); // SSD address low = 0x01
    bus.write(0xF1, 0x00); // SSD address high = 0x00
    std::cout << "SSD[0x0001] (persisted result): " << static_cast<int>(cpu.get_bus().read(0xF2)) << '\n';
}

int main()
{

    std::cout << "=== 1 + 1 Demo (matches user's mental model) ===\n";
    run_one_plus_one_demo();

    std::cout << "=== Compiler Demo: a = 1 + 1 ===\n";

    std::string source_code = "a = 1 + 1";

    Compiler compiler;

    std::vector<uint8_t> bytecode = compiler.compile(source_code);

    Bus compiler_demo_bus;
    compiler_demo_bus.load_program(bytecode);

    Cpu compiler_demo_cpu(compiler_demo_bus);
    compiler_demo_cpu.run();

    uint8_t variable_address = compiler.get_variable_address("a");

    std::cout << "a = " << static_cast<int>(compiler_demo_bus.read(variable_address)) << "\n";

    return 0;
}

