#include "../lib/RAM.h"

#include <stdexcept>

RAM::RAM()
{
    // kho chứa lúc đầu nhẵn bóng
    // vì phải dọn dẹp sạch sẽ
    // lát để đồ vào không bị bẩn 
    // hoặc là hỏng đồ thành phẩm do ô nhiễm
    for (int i = 0; i < 256; i++)
    {
        memory[i] = 0;
    }
}

uint8_t RAM::read(uint8_t address) const
{
    // ông chủ bảo lấy lô thành phẩm
    // ở dãy này về để kiêm tra thêm
    // xem đã đạt tiểu chuẩn chưa
    // hoặc là thành phẩm về để kết hợp với
    // nguyên liệu mới , trộn thành phẩm thành nguyên liệu mới
    return memory[address];
}

void RAM::write(uint8_t address, uint8_t value)
{
    // cất hàng thành phẩm và dãy 
    // này nhé
    memory[address] = value;
}

void RAM::load_program(const std::vector<uint8_t>& bytecode)
{
    if (bytecode.size() > 256)
    {
        throw std::runtime_error("bytecode exceeds RAM capacity");
    }

    for (int i = 0; i < 256; i++)
    {
        memory[i] = 0;
    }

    for (std::size_t i = 0; i < bytecode.size(); i++)
    {
        write(static_cast<uint8_t>(i), bytecode[i]);
    }
}