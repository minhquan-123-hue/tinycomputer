#include "../lib/Bus.h"

Bus::Bus()
{
}

uint8_t Bus::read(uint8_t address) const
{
    if (address < 0xE0)
    {
        return ram.read(address);
    }

    if (address < 0xF0)
    {
        return io_unit.read(address);
    }

    return storage_controller.read(address);
}

void Bus::write(uint8_t address, uint8_t value)
{
    if (address < 0xE0)
    {
        ram.write(address, value);
        return;
    }

    if (address < 0xF0)
    {
        io_unit.write(address, value);
        return;
    }

    storage_controller.write(address, value);
}