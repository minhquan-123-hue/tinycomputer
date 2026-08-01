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
    Bus bus;
    
    // bắt buộc phải có dữ liệu trước nên là bus đã
    // ghi vào trong RAM
    // viết ở 4 địa chỉ đầu tiên: 0,1,2,3
    // hiện tại viết vào trong RAM
    bus.write(0x00, OPCODE_LOAD);
    bus.write(0x01, 0x50);
    
    // cái này cũng viết vào trong RAM
    bus.write(0x02, OPCODE_HALT);
    bus.write(0x03, 0x00);
    
    // sau khi mà đã có dữ liệu ở trong RAM
    // thì khởi tạo ra CPU
    // và sau đó kết nối nó với bus
    Cpu cpu(bus);
    
    // bây giờ ở trong RAM đã có dữ liệu
    // nhưng giờ đọc dữ liệu của programmer_counter chỉ là số nguyên
    // tức là số nguyên này đại diên cho địa chỉ
    std::cout
        << "PC before fetch: "
        << static_cast<int>(cpu.get_registers().get_pc())
        << '\n';
    
    // bây giờ CPU sẽ đọc lệnh + dữ liệu
    // ở trong RAM nhờ anh bus đi đến địa chỉ [0] và [1]
    // vì ngay khi bus được tạo , thì reg cũng được tạo và RAM là một array
    // vậy nên dùng pc là số nguyên đại diện cho địa chỉ của RAM
    // sau đó đi vào array để đọc từng ô một
    FetchedInstruction instruction = cpu.fetch();
    
   // sau khi đi vào trong ô [0] và [1]
   // thành công đọc được dữ liệu mà bus ghi vào lúc đầu
   // và đã được cpu ghi lại thành công vào 
   // dòng lệnh hoàn chỉnh
   // giờ lại trích xuất dòng lệnh hoàn chỉnh đố
   // thanh 2 phần và lôi ra để đọc
    std::cout
        << "Fetched opcode: "
        << static_cast<int>(instruction.opcode_byte)
        << ", operand: "
        << static_cast<int>(instruction.operand_byte)
        << '\n';
    
    // sau khi đọc xong lệnh đầu tiên
    // thì vị trí sẽ được cập nhật đến
    // opcode + opand tiếp theo
    // nhưng hàm get_pc() chỉ để đọc vị trí lệnh hiện tại
    // không phải opcode và opand
    std::cout
        << "PC after fetch: "
        << static_cast<int>(cpu.get_registers().get_pc())
        << '\n';
    
    // đọc vị trí [2] và [3]
    // lệnh + dữ liệu của ram
    instruction = cpu.fetch();
    
    std::cout
        << "Fetched opcode: "
        << static_cast<int>(instruction.opcode_byte)
        << ", operand: "
        << static_cast<int>(instruction.operand_byte)
        << '\n';
    // sau đó đọc vị trí hiện tại sau
    // khi đã check xong lệnh + dữ liệu
    // của PROGRAMING_COUNTER là [4]
    std::cout
        << "PC after fetch: "
        << static_cast<int>(cpu.get_registers().get_pc())
        << '\n';

    // bỏ qua vị trí [5] -> [9]
    // đi thăng đển vị trí của RAM là
    // [10] và [11] để viết lệnh và dữ liệu
    bus.write(0x10, OPCODE_ADD);
    bus.write(0x11, 0x00);

    // thiết vị trí của PROGRAMMING_COUNTER 
    // lên vị trí [10]
    cpu.get_registers().set_pc(0x10);

    // sau đó CPU sẽ hỏi bus đến vị trí của PROGRAMMING_COUNTER
    // hiện tại để đọc lệnh và dữ liệu ở đó
    // và đã lưu lại được lệnh + dữ liệu thành một
    // dòng lệnh hoàn chỉnh
    FetchedInstruction fetched_instruction = cpu.fetch();
    // đưa dòng lệnh hoàn chỉnh vào để kiểm tra xem
    // là opcode có trong TABLE CỦA ROM không
    // hay nói một các thực tế là
    // so sánh các con số hex trong array 
    DecodedInstruction decoded_instruction = cpu.decode(fetched_instruction);

    // và lần so sánh này là valid
    // bởi vì lệnh OPCODE_ADD
    // có trong array hay còn gọi là
    // table của ROM
    std::cout
        << "Decoded opcode: "
        << static_cast<int>(decoded_instruction.opcode)
        << ", operand: "
        << static_cast<int>(decoded_instruction.operand)
        << ", valid: "
        << static_cast<int>(decoded_instruction.is_valid)
        << '\n';

    // tạo ra một số lệnh không có trong bảng opcode_table
    // và sau đó điền vào "truy xuất lệnh"
    FetchedInstruction invalid_instruction;
    invalid_instruction.opcode_byte = 0xFE;
    invalid_instruction.operand_byte = 0x00;

    // đưa vào "giải mã"
    // thì kiểm tra là lệnh
    // không được công nhận
    decoded_instruction = cpu.decode(invalid_instruction);

    std::cout
        << "Decoded opcode: "
        << static_cast<int>(decoded_instruction.opcode)
        << ", operand: "
        << static_cast<int>(decoded_instruction.operand)
        << ", valid: "
        << static_cast<int>(decoded_instruction.is_valid)
        << '\n';

    Alu alu;

    AluResult add_result = alu.add(20, 7);
    std::cout
        << "add(20,7): value="
        << static_cast<int>(add_result.value)
        << " zero="
        << static_cast<int>(add_result.flags.is_zero)
        << " carry="
        << static_cast<int>(add_result.flags.is_carry)
        << " negative="
        << static_cast<int>(add_result.flags.is_negative)
        << '\n';

    AluResult add_overflow_result = alu.add(200, 100);
    std::cout
        << "add(200,100): value="
        << static_cast<int>(add_overflow_result.value)
        << " zero="
        << static_cast<int>(add_overflow_result.flags.is_zero)
        << " carry="
        << static_cast<int>(add_overflow_result.flags.is_carry)
        << " negative="
        << static_cast<int>(add_overflow_result.flags.is_negative)
        << '\n';

    AluResult sub_result = alu.sub(10, 10);
    std::cout
        << "sub(10,10): value="
        << static_cast<int>(sub_result.value)
        << " zero="
        << static_cast<int>(sub_result.flags.is_zero)
        << " carry="
        << static_cast<int>(sub_result.flags.is_carry)
        << " negative="
        << static_cast<int>(sub_result.flags.is_negative)
        << '\n';

    AluResult sub_borrow_result = alu.sub(5, 10);
    std::cout
        << "sub(5,10): value="
        << static_cast<int>(sub_borrow_result.value)
        << " zero="
        << static_cast<int>(sub_borrow_result.flags.is_zero)
        << " carry="
        << static_cast<int>(sub_borrow_result.flags.is_carry)
        << " negative="
        << static_cast<int>(sub_borrow_result.flags.is_negative)
        << '\n';

    AluResult and_result = alu.and_op(0b1100, 0b1010);
    std::cout
        << "and_op(12,10): value="
        << static_cast<int>(and_result.value)
        << " zero="
        << static_cast<int>(and_result.flags.is_zero)
        << " carry="
        << static_cast<int>(and_result.flags.is_carry)
        << " negative="
        << static_cast<int>(and_result.flags.is_negative)
        << '\n';

    AluResult or_result = alu.or_op(0b1100, 0b1010);
    std::cout
        << "or_op(12,10): value="
        << static_cast<int>(or_result.value)
        << " zero="
        << static_cast<int>(or_result.flags.is_zero)
        << " carry="
        << static_cast<int>(or_result.flags.is_carry)
        << " negative="
        << static_cast<int>(or_result.flags.is_negative)
        << '\n';

    AluResult compare_equal_result = alu.compare(10, 10);
    std::cout
        << "compare(10,10): value="
        << static_cast<int>(compare_equal_result.value)
        << " zero="
        << static_cast<int>(compare_equal_result.flags.is_zero)
        << " carry="
        << static_cast<int>(compare_equal_result.flags.is_carry)
        << " negative="
        << static_cast<int>(compare_equal_result.flags.is_negative)
        << '\n';

    AluResult compare_less_result = alu.compare(5, 10);
    std::cout
        << "compare(5,10): value="
        << static_cast<int>(compare_less_result.value)
        << " zero="
        << static_cast<int>(compare_less_result.flags.is_zero)
        << " carry="
        << static_cast<int>(compare_less_result.flags.is_carry)
        << " negative="
        << static_cast<int>(compare_less_result.flags.is_negative)
        << '\n';
}

