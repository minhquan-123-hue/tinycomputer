#ifndef REGISTERS_H
#define REGISTERS_H

// this class contain "blue print"
// of unsign int 8 bit.
#include <cstdint>

static constexpr uint8_t STACK_POINTER_START = 0xDF;

struct Flags
{
    bool is_zero = false;
    bool is_carry = false;
    bool is_negative = false;
};

class REGISTERS
{
public:
    REGISTERS();

    void set_a(uint8_t value);
    uint8_t get_a() const;

    void set_b(uint8_t value);
    uint8_t get_b() const;

    uint8_t get_pc() const;
    void set_pc(uint8_t value);

    uint8_t get_sp() const;
    void set_sp(uint8_t value);

    Flags get_flags() const;
    void set_flags(Flags new_flags);

    void increment_pc();

private:
    uint8_t reg_a;
    uint8_t reg_b;
    uint8_t program_counter;
    uint8_t stack_pointer;
    Flags flags;
};

#endif