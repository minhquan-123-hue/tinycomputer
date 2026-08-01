#include "../lib/Alu.h"

AluResult Alu::add(uint8_t left_operand, uint8_t right_operand) const
{
    uint16_t raw_sum = static_cast<uint16_t>(left_operand) + right_operand;
    uint8_t result = static_cast<uint8_t>(raw_sum);
    bool is_carry = raw_sum > 0xFF;

    return AluResult{result, compute_flags(result, is_carry)};
}

AluResult Alu::sub(uint8_t left_operand, uint8_t right_operand) const
{
    bool is_carry = left_operand < right_operand;
    uint8_t result = static_cast<uint8_t>(left_operand - right_operand);

    return AluResult{result, compute_flags(result, is_carry)};
}

AluResult Alu::and_op(uint8_t left_operand, uint8_t right_operand) const
{
    uint8_t result = static_cast<uint8_t>(left_operand & right_operand);

    return AluResult{result, compute_flags(result, false)};
}

AluResult Alu::or_op(uint8_t left_operand, uint8_t right_operand) const
{
    uint8_t result = static_cast<uint8_t>(left_operand | right_operand);

    return AluResult{result, compute_flags(result, false)};
}

AluResult Alu::compare(uint8_t left_operand, uint8_t right_operand) const
{
    bool is_carry = left_operand < right_operand;
    uint8_t result = static_cast<uint8_t>(left_operand - right_operand);

    return AluResult{result, compute_flags(result, is_carry)};
}

Flags Alu::compute_flags(uint8_t result, bool is_carry) const
{
    Flags flags;
    flags.is_zero = result == 0;
    flags.is_negative = (result & 0x80u) != 0;
    flags.is_carry = is_carry;

    return flags;
}
