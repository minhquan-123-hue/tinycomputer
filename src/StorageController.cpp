#include "../lib/StorageController.h"

StorageController::StorageController()
{
}

bool StorageController::is_address_in_range(uint16_t disk_address) const
{   
    // kiểm tra ông chủ xương hỏi đúng dãy chứa
    // nguyên liệu của kho nguyên liệu chưa
    // nếu đúng dãy thì bảo ông chủ là đúng rồi ông
    // và ngược lại
    // bởi vì ông chủ tìm nguyên liệu nào , thì nguyên
    // liệu phải nằm đúng trong kho thì mới có còn không có thể
    // là nhầm dãy hoặc hết nguyê liệu đó rồi
    return disk_address < DISK_SIZE;
}

void StorageController::set_address_low(uint8_t value)
{
    // ông chủ muốn kiểm tra dãy nhưng
    // nhớ được có 1 nửa địa chỉ của dãy
    // rồi anh bus đã nói luôn cho quản lý kho nguyên
    // liệu
    current_address = static_cast<uint16_t>((current_address & 0xFF00u) | value);
}

void StorageController::set_address_high(uint8_t value)
{
    // sau đó anh bus lại nói , hoặc giao nốt
    // vị trí dãy còn lại cho 
    // quản lý 
    current_address = static_cast<uint16_t>((current_address & 0x00FFu) | (static_cast<uint16_t>(value) << 8));
}

uint8_t StorageController::read(uint8_t address) const
{
    // quản lý kiểm tra yêu cầu của ông
    // chủ có phải là muốn lấy nguyên liệu thô
    // từ kho không
    if (address != DATA_READ_REGISTER)
    {
        return 0;
    }

    // kiểm tra lại xem dãy chứa hàng có nằm
    // trong kho không
    if (!is_address_in_range(current_address))
    {
        return 0;
    }

    // nếu có dãy ,thì đến dãy
    // và đưa cho anh bus
    // mang nguyên liệu thô về để còn chế biến
    return disk_buffer[current_address];
}

void StorageController::write(uint8_t address, uint8_t value)
{
    // low + high = vị trí cất lương thực thô cần thiết
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

    // nếu trong bức thư yêu cầu kiểm tra sai vị trí của
    // hàng hóa trong kho thì nó sẽ là không thể
    // tìm được hàng vậy nếu báo là tìm sai vị trí lại
    // luôn cho ổng chủ xưởng sản xuất
    if (!is_address_in_range(current_address))
    {
        return;
    }

    // sau khi đã báo đúng vị trí cất hàng chuẩn
    // thì sau đó là sẽ vào đúng vị trí cất hàng 
    // và sau đó là để hàng vào ô đó 
    disk_buffer[current_address] = value;
}