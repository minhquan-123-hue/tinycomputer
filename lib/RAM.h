#ifndef RAM_H
#define RAM_H

#include <cstdint>

class RAM
{
public:
    RAM();

    uint8_t read(uint8_t address) const;
    void write(uint8_t address, uint8_t value);

private:
    uint8_t memory[256];
};

#endif