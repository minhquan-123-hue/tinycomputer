#ifndef REGISTERS_H
#define REGISTERS_H

// this class contain "blue print"
// of unsign int 8 bit.
#include <cstdint>

// vị trí bắt đầu của con trỏ vùng stack
static constexpr uint8_t STACK_POINTER_START = 0xDF;

// báo hiệu vừa thực hiện số ở trên
// âm , dương, hoặc là nhớ tiếp theo
struct Flags
{
    bool is_zero = false;
    bool is_carry = false;
    bool is_negative = false;
};

class Registers
{
public:
    Registers();

    // nhớ các con số để thực hiện phép tính
    void set_a(uint8_t value);
    uint8_t get_a() const;

    void set_b(uint8_t value);
    uint8_t get_b() const;

    // ngón tay chỉ "tập lệnh" tiếp theo
    // để có thể chương trình có thể hoạt động
    uint8_t get_pc() const;
    void set_pc(uint8_t value);

    // nhét dữ liệu mà register tạm thời không lưu
    // để tính toán được hế trong thời điểm hiện tại
    // nó sẽ để tạm ở trong ram và sau đó lấy ra để tính
    // toán sau 
    uint8_t get_sp() const;
    void set_sp(uint8_t value);

    // đọc trạng thái tính toán hiện tại
    // xem âm hay dương, hay là nhớ
    // để tính tiếp trong intructions tiếp theo
    Flags get_flags() const;
    void set_flags(Flags new_flags);

    // đọc lời chỉ dẫn tiếp theo
    void increment_pc();

private:
    // thanh ghi lưu số để tính toán
    uint8_t reg_a;
    uint8_t reg_b;
    // thanh ghi được dùng để đọc lệnh tiếp theo
    // để thực thi chương trình
    uint8_t program_counter;
    // thanh ghi được dùng để đọc dữ liệu trong
    // ram khi mà không lưu được hết
    // trong thanh ghi
    uint8_t stack_pointer;
    // trạng thái tính toán hiện tại
    // âm dương nhớ
    Flags flags;
};

#endif