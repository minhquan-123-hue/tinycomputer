#include "../lib/REGISTERS.h"

REGISTERS::REGISTERS()
    : reg_a(0),
      reg_b(0),
      program_counter(0),
      stack_pointer(STACK_POINTER_START),
      flags()
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

uint8_t REGISTERS::get_pc() const
{
    return program_counter;
}

void REGISTERS::set_pc(uint8_t value)
{
    program_counter = value;
}

uint8_t REGISTERS::get_sp() const
{
    return stack_pointer;
}

void REGISTERS::set_sp(uint8_t value)
{
    stack_pointer = value;
}

Flags REGISTERS::get_flags() const
{
    return flags;
}

void REGISTERS::set_flags(Flags new_flags)
{
    flags = new_flags;
}

void REGISTERS::increment_pc()
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