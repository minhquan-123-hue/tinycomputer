#ifndef ALU_H
#define ALU_H

#include <cstdint>
#include "Registers.h"

// cái này đơn giản là 
// nơi lưu kết quả của phép tính
// và cờ báo : âm , dương hoặc là "nhớ"
struct AluResult
{
    uint8_t value;
    Flags flags;
};

class Alu
{
public:
    AluResult add(uint8_t left_operand, uint8_t right_operand) const;
    AluResult sub(uint8_t left_operand, uint8_t right_operand) const;
    AluResult and_op(uint8_t left_operand, uint8_t right_operand) const;
    AluResult or_op(uint8_t left_operand, uint8_t right_operand) const;
    AluResult compare(uint8_t left_operand, uint8_t right_operand) const;

private:
    Flags compute_flags(uint8_t result, bool is_carry) const;
};

#endif
