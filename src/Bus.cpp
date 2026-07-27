#include "../lib/Bus.h"

Bus::Bus()
{
}

uint8_t Bus::read(uint8_t address)
{
    // mỗi bộ địa chỉ == bức thư
    // và nó sẽ đưa cho anh vận chuyển
    // nếu xưởng sản xuất bảo giao đế kho thành phẩm
    // thì anh đến nhà kho thành phẩm
    // để lấy hàng thành phẩm về để kiểm tra
    if (address < 0xE0)
    {
        return ram.read(address);
    }

    // nếu thư là nhận hàng ở cổng thương mại
    // thì anh không đi đường của kho chứa thành phẩm nữa
    // mà ra cổng thương mại ở bãi luôn
    if (address < 0xF0)
    {
        // anh phải đi đúng vào chỗ để hàng
        // và sau nhận hàng về
        return io_unit.read(address - 0xE0);
    }

    // nếu xưởng bảo là vào lấy hàng ở kho nguyên liệu thô
    // thì anh giao hàng vào kho lấy nguyên liệu chứ
    // không ra cổng thưởng mại xuất khẩu hàng,
    // hoặc cất hàng vào kho thành phẩm
    return storage_controller.read(address - 0xF0);
}

void Bus::write(uint8_t address, uint8_t value)
{
    // khi mà xưởng yêu cầu cất hàng làm xong 
    // vào kho thành phẩm thì anh giao hàng
    // chạy mọt mạch ra kho giao hàng để cất hàng đó
    if (address < 0xE0)
    {
        ram.write(address, value);
        return; // sau đó anh ngồi nghỉ ngơi
    }

    // nếu mà xưởng yêu cầu anh giao hàng
    // mang ra cổng thương mại để xuất khẩu hàng
    // đi quốc tế , thì anh lại vội vã đi
    // ra cổng thương mai để giao hàng ngay
    if (address < 0xF0)
    {
        io_unit.write(address - 0xE0, value);
        return;
    }

    // và nếu xương bảo anh cất nguyên liệu thô
    // về kho thì anh cũng tháo vát làm ngay
    // chẳng nề hà tí nào
    storage_controller.write(address - 0xF0, value);
}

IoUnit& Bus::get_io_unit()
{
    // nếu được lệnh là mang hợp đồng giao dịch
    // của công ty "cổng thương mại" về để 
    // ổng chủ xưởng xem xét và sau đó liên hệ trực
    // tiếp với bên đó , để không phải làm 2 bản hợp đồng
    // mà làm việc trực tiếp với nhau luôn.
    return io_unit;
}