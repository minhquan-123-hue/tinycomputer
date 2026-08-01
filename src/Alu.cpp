#include "../lib/Alu.h"

// hàm này làm cộng như phép tính bình thường
// và có ma thuật bên dưới nên vẫn sẽ không thể hiểu cách
// ALU tính toán
AluResult Alu::add(uint8_t left_operand, uint8_t right_operand) const
{
    // dùng 16 bit để lấy kết quả đúng
    uint16_t raw_sum = static_cast<uint16_t>(left_operand) + right_operand;
    // sau đó ép kết quả thành nhỏ hơn = 255
    // còn nếu kết quả lớn hơn thì uint dùng phép chia lấy dư
    // để biến số lớn hơn nằm trong phạm vi <= 255
    uint8_t result = static_cast<uint8_t>(raw_sum);
    // so sánh kết nếu lớn hơn thì tạo cờ true
    bool is_carry = raw_sum > 0xFF;

    return AluResult{result, compute_flags(result, is_carry)};
}

AluResult Alu::sub(uint8_t left_operand, uint8_t right_operand) const
{
    bool is_carry = left_operand < right_operand;
    uint8_t result = static_cast<uint8_t>(left_operand - right_operand);

    return AluResult{result, compute_flags(result, is_carry)};
}

// lọc bit , dùng bitwise
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

// so sánh 2 số 
// nếu số này trừ số kia = âm => nhỏ hơn
// ngược lại ra dương thì tức là lớn hơn
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
