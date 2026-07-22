#ifndef BUS_H
#define BUS_H

#include <cstdint>
#include "RAM.h"
#include "IoUnit.h"
#include "StorageController.h"

class Bus
{
public:
    Bus();

    uint8_t read(uint8_t address) const;
    void write(uint8_t address, uint8_t value);

private:
    RAM ram;
    IoUnit io_unit;
    StorageController storage_controller;
};

#endif