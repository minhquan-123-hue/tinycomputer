#ifndef RAM_H
#define RAM_H

#include <cstdint>

// kho chứa thành phẩm : hàng thì có hạn , nếu không giao ngay thì là hết hạn
class RAM
{
public:
    RAM();

    // ông chủ xưởng muốn lấy nguyên liệu thành phẩm
    // về xưởng để chế tạo thêm
    uint8_t read(uint8_t address) const;
    // ông chủ yêu cầu cất hàng thành phẩm vào kho
    // để xuất khẩu, hoặc để tí trộn thêm với nguyên liệu
    // khác sau
    void write(uint8_t address, uint8_t value);

private:
    // kích thức của kho chứa thành phẩm
    uint8_t memory[256];
};

#endif