#include "../lib/StorageController.h"

StorageController::StorageController()
{
}

bool StorageController::is_address_in_range(uint16_t disk_address) const
{
    return disk_address < DISK_SIZE;
}

void StorageController::set_address_low(uint8_t value)
{
    current_address = static_cast<uint16_t>((current_address & 0xFF00u) | value);
}

void StorageController::set_address_high(uint8_t value)
{
    current_address = static_cast<uint16_t>((current_address & 0x00FFu) | (static_cast<uint16_t>(value) << 8));
}

uint8_t StorageController::read(uint8_t address) const
{
    // nếu "thư" yêu cầu đúng là đọc
    // thì sau đó kiểm tra
    if (address != DATA_READ_REGISTER)
    {
        return 0;
    }

    // địa chỉ hiện tại đang đứng trong ssd
    // là ở đâu, để nhét thêm nguyên liệu thô
    // vào
    if (!is_address_in_range(current_address))
    {
        return 0;
    }

    return disk_buffer[current_address];
}

void StorageController::write(uint8_t address, uint8_t value)
{
    // low + high = địa chỉ cất lương thực thô cần thiết
    // có thể là bột năng, cà rốt (ảnh , video,...)
    if (address == ADDRESS_LOW_REGISTER)
    {
        set_address_low(value);
        return;
    }

    if (address == ADDRESS_HIGH_REGISTER)
    {
        set_address_high(value);
        return;
    }

    // nếu "thư" không yêu cầu viết thì dừng lại
    if (address != DATA_WRITE_REGISTER)
    {
        return;
    }

    if (!is_address_in_range(current_address))
    {
        return;
    }

    disk_buffer[current_address] = value;
}