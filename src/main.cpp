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

    // viết dữ liệu vào trong ram
    // đây 5 câu lệnh tương ứng với 10 địa chỉ [opcode + opand]
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

    // thiết lập con trỏ ở vị trí đầu tiên
    execution_cpu.get_registers().set_pc(0x00);

    RunResult execution_run_result = execution_cpu.run();

    std::cout << "Instructions executed: " << execution_run_result.instructions_executed << '\n';
    std::cout << "Valid opcode (clean halt): " << static_cast<int>(execution_run_result.is_valid_opcode) << '\n';
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

    RunResult jump_run_result = jump_cpu.run();

    std::cout << "JMP test — A register (should be unchanged, confirming skip worked): "
              << static_cast<int>(jump_cpu.get_registers().get_a()) << '\n';
    std::cout << "JMP run instructions executed: " << jump_run_result.instructions_executed << '\n';
    std::cout << "JMP run valid opcode: " << static_cast<int>(jump_run_result.is_valid_opcode) << '\n';

    Bus infinite_loop_bus;
    Cpu infinite_loop_cpu(infinite_loop_bus);

    infinite_loop_bus.write(0x00, OPCODE_JMP);
    infinite_loop_bus.write(0x01, 0x00);

    infinite_loop_cpu.get_registers().set_pc(0x00);

    RunResult infinite_loop_result = infinite_loop_cpu.run();

    std::cout << "Infinite loop test — instructions executed (should equal cap): "
              << infinite_loop_result.instructions_executed << '\n';
    std::cout << "Infinite loop valid opcode: " << static_cast<int>(infinite_loop_result.is_valid_opcode) << '\n';

}

