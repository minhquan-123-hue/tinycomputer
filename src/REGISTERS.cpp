#include "../lib/REGISTERS.h"

REGISTERS::REGISTERS()
    : reg_a(0),
      reg_b(0)
{
}

void REGISTERS::set_a(uint8_t value)
{
    reg_a = value;
}

// read-only function 
uint8_t REGISTERS::get_a() const
{
    return reg_a;
}

void REGISTERS::set_b(uint8_t value)
{
    reg_b = value;
}

uint8_t REGISTERS::get_b() const
{
    return reg_b;
}