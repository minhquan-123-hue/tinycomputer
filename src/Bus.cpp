#include "../lib/Bus.h"

Bus::Bus()
{
}

uint8_t Bus::read(uint8_t address)
{
    // each component have it own "short-term" memory + address
    // cpu can procduce 256 address
    // RAM 244, I/O 16 , SC 16
    if (address < 0xE0)
    {
        return ram.read(address);
    }

    if (address < 0xF0)
    {
        return io_unit.read(address - 0xE0);
    }

    return storage_controller.read(address - 0xF0);
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
        io_unit.write(address - 0xE0, value);
        return;
    }

    storage_controller.write(address - 0xF0, value);
}

IoUnit& Bus::get_io_unit()
{
    return io_unit;
}