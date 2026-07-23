#ifndef IO_UNIT_H
#define IO_UNIT_H

#include <cstdint>
#include <queue>

class IoUnit
{
public:
    IoUnit();

    // Reading key data removes the next key from the input queue.
    uint8_t read(uint8_t local_address);
    void write(uint8_t local_address, uint8_t value);
    void push_key_input(uint8_t key);

private:
    bool is_key_available() const;

    static constexpr uint8_t STATUS_REGISTER = 0x00;
    static constexpr uint8_t KEY_DATA_REGISTER = 0x01;
    static constexpr uint8_t OUTPUT_REGISTER = 0x02;

    std::queue<uint8_t> key_queue;
};

#endif