#ifndef IO_UNIT_H
#define IO_UNIT_H

#include <cstdint>
#include <queue>

// cổng thương mại: chuyên xuất khẩu , và nhập khẩu hàng hóa
class IoUnit
{
public:
    IoUnit();

    // khi được ông chủ hỏi xem có hàng không
    uint8_t read(uint8_t local_address);
    // khi được ổng chủ xưởng hỏi giao hàng đi nước bạn
    void write(uint8_t local_address, uint8_t value);
    // khi mà nhận được được hàng từ bên bển giao
    // về
    void push_key_input(uint8_t key);

private:
    // khi mà vào kho kiểm tra xem có 
    //  hàng của bên bển giao về không
    bool is_key_available() const;

    // bức thư của ông chủ xưởng
    // nội dung hoặc + yêu cầu
    static constexpr uint8_t STATUS_REGISTER = 0x00;
    static constexpr uint8_t KEY_DATA_REGISTER = 0x01;
    static constexpr uint8_t OUTPUT_REGISTER = 0x02;

    // ống chứa hàng 1 chiều
    std::queue<uint8_t> key_queue;
};

#endif