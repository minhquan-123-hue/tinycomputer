#ifndef CPU_H
#define CPU_H

#include <cstdint>

#include "../lib/Bus.h"
#include "../lib/Registers.h"
#include "../lib/Intructions.h"
#include "../lib/Alu.h"

// câu lệnh có 2 phần
// lệnh + dữ liệu
struct FetchedInstruction
{
    uint8_t opcode_byte;
    uint8_t operand_byte;
};

struct DecodedInstruction
{
    uint8_t opcode;
    uint8_t operand;
    bool is_valid;
};

struct ExecuteResult
{
    bool is_halted;
    bool is_valid_opcode;
};

class Cpu
{
public:
    // dòng mã này có nghĩa là
    // bất kỳ cpu mới nào để phải sử dụng
    // với đường bus có sẵn của hệ thống
    // để có thể kết nối đến ram, ssd,màn hình,
    // vân vân
    explicit Cpu(Bus& bus);

    // đọc lệnh hiện tại 
    // đưa cho ALU để thực thi
    FetchedInstruction fetch();
    // sau khi đã có lệnh hợp nhất
    // thì sau đó giải mã chúng ra
    DecodedInstruction decode(const FetchedInstruction& fetched_instruction) const;
    ExecuteResult execute(const DecodedInstruction& decoded_instruction);

    // máy sửa lỗi, kiểm tra 
    // các trạng thái hiện tại của registers
    // stack pointer đã đúng vị trí chưa
    // pc đang ở đâu.
    Registers& get_registers();
    Bus& get_bus();

private:
    // kiểm tra xem lệnh mà được tạo ra có
    // trong table những câu lệnh mà CPU biết không
    // nếu không thì dừng chương trình 
    bool is_known_opcode(uint8_t opcode_byte) const;

    void apply_alu_result(const AluResult& alu_result);

    // toàn quyền sở hữu
    Registers registers;
    // tham chiếu
    // và nhờ vả "write" và "read"
    // 
    Bus& bus;
    Alu alu;
};

#endif