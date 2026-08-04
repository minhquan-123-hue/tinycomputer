#include "../lib/Cpu.h"
#include <iostream>

Cpu::Cpu(Bus& bus)
    : bus(bus)
{
}

FetchedInstruction Cpu::fetch()
{
    // đọc bộ đếm dòng lệnh
    // sau đó đọc "lệnh" + "nội dung"
    // nhét nó vào một lệnh hoàn chỉnh
    uint8_t program_counter = registers.get_pc();
    std::cout << program_counter << "\n";

    // đưa vào cấu trúc dữ liệu
    // để có thể nhóm thành 1 lệnh hoàn chỉnh
    FetchedInstruction instruction;

    // đọc trong RAM
    // lệnh từ vị trí 0 là lệnh gì
    // dữ liệu ở vị trí 1 là nội dung gì
    // đưa từng lệnh đó vào trong cấu trúc dữ liệu struct
    // điền thành 1 lệnh hoàn chỉnh
    instruction.opcode_byte = bus.read(program_counter);
    instruction.operand_byte = bus.read(program_counter + 1);

    // tăng vị trí của con trỏ lên 2 lần
    // vì vị trí lệnh mô phỏng RAM
    // đang là một array và RAM cũng là một ARRAY
    // vậy nên để đọc được lệnh và dữ liệu tiếp theo
    registers.increment_pc();
    registers.increment_pc();

    // trả lại tập lệnh hoàn chỉnh
    return instruction;
}

DecodedInstruction Cpu::decode(const FetchedInstruction& fetched_instruction) const
{
    // kiểm tra rất đơn giản 
    // chỉ đơn giản là xem nó có trong
    // table lệnh của CPU không
    DecodedInstruction decoded_instruction;

    decoded_instruction.opcode = fetched_instruction.opcode_byte;
    decoded_instruction.operand = fetched_instruction.operand_byte;

    decoded_instruction.is_valid = is_known_opcode(fetched_instruction.opcode_byte);

    return decoded_instruction;
}

bool Cpu::is_known_opcode(uint8_t opcode_byte) const
{
    // tạo một array chứa tất cả opcodes
    // của cpu biết
    // so sánh với lệnh đọc được trong RAM
    // nếu khớp CPU chạy lệnh
    // nếu không khớp thì dừng
    // chỉ đơn giản vậy thôi.
    constexpr uint8_t known_opcodes[] = {
        OPCODE_HALT, OPCODE_LOAD, OPCODE_STORE, OPCODE_MOV_A_B, OPCODE_MOV_B_A,
        OPCODE_ADD, OPCODE_SUB, OPCODE_AND_OP, OPCODE_OR_OP, OPCODE_JMP,
        OPCODE_JZ, OPCODE_LOAD_IMM
    };

    for (uint8_t known_opcode : known_opcodes)
    {
        if (known_opcode == opcode_byte)
        {
            return true;
        }
    }

    return false;
}

ExecuteResult Cpu::execute(const DecodedInstruction& decoded_instruction)
{
    if (!decoded_instruction.is_valid)
    {
        return {true, false};
    }

    switch (decoded_instruction.opcode)
    {
    case OPCODE_HALT:
        return {true, true};
    case OPCODE_LOAD:
        registers.set_a(bus.read(decoded_instruction.operand));
        break;
    case OPCODE_STORE:
        bus.write(decoded_instruction.operand, registers.get_a());
        break;
    case OPCODE_MOV_A_B:
        registers.set_b(registers.get_a());
        break;
    case OPCODE_MOV_B_A:
        registers.set_a(registers.get_b());
        break;
    case OPCODE_ADD:
        apply_alu_result(alu.add(registers.get_a(), registers.get_b()));
        break;
    case OPCODE_SUB:
        apply_alu_result(alu.sub(registers.get_a(), registers.get_b()));
        break;
    case OPCODE_AND_OP:
        apply_alu_result(alu.and_op(registers.get_a(), registers.get_b()));
        break;
    case OPCODE_OR_OP:
        apply_alu_result(alu.or_op(registers.get_a(), registers.get_b()));
        break;
    case OPCODE_JMP:
        registers.set_pc(decoded_instruction.operand);
        break;
    case OPCODE_JZ:
        if (registers.get_flags().is_zero)
        {
            registers.set_pc(decoded_instruction.operand);
        }
        break;
    case OPCODE_LOAD_IMM:
        registers.set_a(decoded_instruction.operand);
        break;
    default:
        return {true, false};
    }

    return {false, true};
}

void Cpu::apply_alu_result(const AluResult& alu_result)
{
    registers.set_a(alu_result.value);
    registers.set_flags(alu_result.flags);
}

Registers& Cpu::get_registers()
{
    // đọc nội dung của thanh ghi
    // xem pc,sp
    return registers;
}

Bus& Cpu::get_bus()
{
    return bus;
}