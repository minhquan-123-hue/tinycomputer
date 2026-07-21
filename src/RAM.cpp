#include "../lib/RAM.h"

RAM::RAM()
{
    for (int i = 0; i < 256; i++)
    {
        memory[i] = 0;
    }
}

uint8_t RAM::read(uint8_t address) const
{
    return memory[address];
}

void RAM::write(uint8_t address, uint8_t value)
{
    memory[address] = value;
}