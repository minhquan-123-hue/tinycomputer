#ifndef IO_UNIT_H
#define IO_UNIT_H

#include <cstdint>

class IoUnit
{
public:
    IoUnit();

    uint8_t read(uint8_t address) const;
    void write(uint8_t address, uint8_t value);
};

#endif