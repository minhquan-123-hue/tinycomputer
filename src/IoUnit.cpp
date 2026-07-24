#include "../lib/IoUnit.h"
#include <iostream>

IoUnit::IoUnit()
{
}

uint8_t IoUnit::read(uint8_t local_address)
{
    if (local_address == STATUS_REGISTER)
    {
        return is_key_available() ? 1 : 0;
    }

    if (local_address != KEY_DATA_REGISTER || !is_key_available())
    {
        return 0;
    }

    uint8_t key = key_queue.front();
    key_queue.pop();
    return key;
}

bool IoUnit::is_key_available() const
{
    // method check "1 direction pipe"
    return !key_queue.empty();
}

void IoUnit::push_key_input(uint8_t key)
{
    key_queue.push(key);
}

void IoUnit::write(uint8_t local_address, uint8_t value)
{
    if (local_address != OUTPUT_REGISTER)
    {
        return;
    }

    std::cout << static_cast<char>(value);
}