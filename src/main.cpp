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

    bus.write(0x10, OPCODE_ADD);
    bus.write(0x11, 0x00);

    cpu.get_registers().set_pc(0x10);

    FetchedInstruction fetched_instruction = cpu.fetch();
    DecodedInstruction decoded_instruction = cpu.decode(fetched_instruction);

    std::cout
        << "Decoded opcode: "
        << static_cast<int>(decoded_instruction.opcode)
        << ", operand: "
        << static_cast<int>(decoded_instruction.operand)
        << ", valid: "
        << static_cast<int>(decoded_instruction.is_valid)
        << '\n';

    FetchedInstruction invalid_instruction;
    invalid_instruction.opcode_byte = 0xFE;
    invalid_instruction.operand_byte = 0x00;

    decoded_instruction = cpu.decode(invalid_instruction);

    std::cout
        << "Decoded opcode: "
        << static_cast<int>(decoded_instruction.opcode)
        << ", operand: "
        << static_cast<int>(decoded_instruction.operand)
        << ", valid: "
        << static_cast<int>(decoded_instruction.is_valid)
        << '\n';
}

