#ifndef REGISTERS_H
#define REGISTERS_H

// this class contain "blue print"
// of unsign int 8 bit.
#include <cstdint>

class REGISTERS
{
public:
    REGISTERS();

    void set_a(uint8_t value);
    uint8_t get_a() const;

    void set_b(uint8_t value);
    uint8_t get_b() const;

private:
    uint8_t reg_a;
    uint8_t reg_b;
};

#endif