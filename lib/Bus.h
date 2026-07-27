#ifndef BUS_H
#define BUS_H

#include <cstdint>
#include "RAM.h"
#include "IoUnit.h"
#include "StorageController.h"

// anh vận chuyển trong nước may mắn
class Bus
{
public:
    Bus();

    // anh đi giao thư khớp nơi trong nước
    // lúc thì mang thư về cho chủ xưởng
    // lúc thì mang thư yêu cầu công việc + hoặc hàng hóa thành phầm từ xưởng giao đi
    uint8_t read(uint8_t address);
    void write(uint8_t address, uint8_t value);
    IoUnit& get_io_unit();

private:
    // kho chứa tạm thời ở xa
    RAM ram;
    // cổng thương mại
    // xuất khẩ hàng với quốc tế , và nhận 
    // nhập khẩu hàng với quốc tế
    IoUnit io_unit;
    // quản lý của kho chứa
    // nguyên liệu thô
    StorageController storage_controller;
};

#endif