#include "../lib/Registers.h"

Registers::Registers()
    : reg_a(0),
      reg_b(0),
      program_counter(0),
      stack_pointer(STACK_POINTER_START),
      flags()
{
}

// nhét dữ liệu vào trong thanh ghi a
void Registers::set_a(uint8_t value)
{
    reg_a = value;
}

// đọc dữ liệu trong thanh ghi a
uint8_t Registers::get_a() const
{
    return reg_a;
}

// nhét dữ liệu vào trong thanh ghi b
void Registers::set_b(uint8_t value)
{
    reg_b = value;
}

// đọc dữ liệu trong thanh ghi b
uint8_t Registers::get_b() const
{
    return reg_b;
}

// đọc vị trí hiện tại của thanh ghi b
uint8_t Registers::get_pc() const
{
    return program_counter;
}

// chỉ đến lệnh tiếp theo để đọc lệnh chỉ dẫn
void Registers::set_pc(uint8_t value)
{
    program_counter = value;
}

// đọc vị trí của con trỏ ngăn xếp hiện tại
uint8_t Registers::get_sp() const
{
    return stack_pointer;
}

// thiết lập con trỏ ngăn xếp đến vị trí tiếp theo
// để có thể đọc dữ liệu bên trong 
void Registers::set_sp(uint8_t value)
{
    stack_pointer = value;
}

// đọc trạng thai hiện tại
// của cờ tính toán hiện tại là âm hay dương, nhớ 
// để sang trạng thái tiếp theo để tính
Flags Registers::get_flags() const
{
    return flags;
}

// thiết lập trạng thái tính toán 
// hiện tại là âm,dương,nhớ
// để tính sang lệnh tiếp theo đọc
// lại xem là biết cpu đang tính cái
// gì lệnh trước đó 
void Registers::set_flags(Flags new_flags)
{
    flags = new_flags;
}

// đọc lệnh tiếp theo
// để có thể tính toán 
// cái tiếp theo làm là cái gì
void Registers::increment_pc()
{
    if (program_counter == 0xFF)
    {
        program_counter = 0;
    }
    else
    {
        program_counter++;
    }
}