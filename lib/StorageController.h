#ifndef STORAGE_CONTROLLER_H
#define STORAGE_CONTROLLER_H

#include <array>
#include <cstdint>

class StorageController
{
public:
    // các bức thư : nội dung + nhiệm vụ
    // nếu sau này các bức thư của ông chủ xưởng yêu cầu khớp
    // thì sẽ chạy mã của các hàm
    static constexpr uint8_t ADDRESS_LOW_REGISTER = 0x00;
    static constexpr uint8_t ADDRESS_HIGH_REGISTER = 0x01;
    static constexpr uint8_t DATA_READ_REGISTER = 0x02;
    static constexpr uint8_t DATA_WRITE_REGISTER = 0x03;
    static constexpr uint16_t DISK_SIZE = 4096;

    StorageController();

    // ông chủ xưởng bảo muốn lấy nguyên liệu thô
    uint8_t read(uint8_t address) const;
    // ông chủ muốn cất lại nguyên liệu thô
    void write(uint8_t address, uint8_t value);

private:
    // dòng này để kiểm tra xem phải địa
    // nằm trong phạm vi của DISK không
    bool is_address_in_range(uint16_t disk_address) const;
    void set_address_low(uint8_t value);
    void set_address_high(uint8_t value);

    // đây là kích thước của toàn bộ đĩa
    // toàn bộ không gian của kho chứa nguyên
    // liệu thô
    std::array<uint8_t, DISK_SIZE> disk_buffer{};
    /// toàn bộ các tủ chứa đồ đều trống hiện tại.
    uint16_t current_address{0};
};

#endif