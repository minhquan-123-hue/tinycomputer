#ifndef STORAGE_CONTROLLER_H
#define STORAGE_CONTROLLER_H

#include <cstdint>

class StorageController
{
public:
    StorageController();

    uint8_t read(uint8_t address) const;
    void write(uint8_t address, uint8_t value);
};

#endif