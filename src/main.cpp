#include <iostream>
#include <iomanip>
#include "../lib/Bus.h"
#include "../lib/RAM.h"
#include "../lib/REGISTERS.h"

int main()
{
    // khởi bộ nhớ tam ở xa nhiều ngăn
    RAM ram;

    // nhét dữ liệu vào trong ram
    ram.write(0, 25);
    ram.write(1, 99);
    ram.write(2, 42);

    std::cout << "Address    Value\n";
    std::cout << "-------    -----\n";

    // sau đó đọc dữ liệu trong ram
    // hiển thị nó lên màn hình
    for (int address = 0; address < 3; address++)
    {
        std::cout << std::left
                  << std::setw(11) << address
                  << (int)ram.read(address)
                  << "\n";
    }
    std::cout << "\n";


    // thanh ghi có thể có là bức thư
    // đồng thời là bộ nhớ tạm thời ở gần
    // để mà cpu có thể sử dụng đế tính toán 
    // các phép tính.
    REGISTERS registers;

    registers.set_a(15);
    registers.set_b(99);

    // sau khi điền dữ liệu trong thanh
    // ta có thể đọc nội dung bên trong của nó
    // chỉ là mô phỏng , thường thì sẽ không thể đọc trực tiếp như thế này
    // chỉ có các kỹ sử ở tầng thấp nhất họ mới đọc
    std::cout << "A = " << static_cast<int>(registers.get_a()) << '\n';
    std::cout << "B = " << static_cast<int>(registers.get_b()) << "\n\n";


    // anh giao hàng nội địa
    // có khả năng biết tất cả địa chỉ
    // và mang "bức thư" chứa nội dung + nhiệm vụ
    // đi khắp mọi nơi
    Bus bus;
    
    // hiện tại bus đang giao hàng đến io 
    // sau đó io sẽ đưa cho màn hình hiển thì nó lên
    bus.write(0xE2, 'H');
    bus.write(0xE2, 'i');
    bus.write(0xE2, '\n');

    // đọc dữ liệu trong đường truyền của io có trước khi
    // nó chuyển ra cho màn hình
    std::cout << "IO status (before key): "
              << static_cast<int>(bus.read(0xE0)) << '\n';

    // hỏi bus là giao chữ X cho IO
    // sau đó nó sẽ truyền dữ liệu trên ra màn hình
    bus.get_io_unit().push_key_input('X');

    // trước khi có phím được nhấn
    std::cout << "IO status (after key): "
              << static_cast<int>(bus.read(0xE0)) << '\n';
    // phím nhấn được đổi thành số
    std::cout << "IO key data: "
              << static_cast<int>(bus.read(0xE1)) << '\n';
    // sau khi đọc phím thành công
    // xóa phím khỏi hàng đợi để có thể đọc phím khác,
    // hoặc là lưu phím khác
    std::cout << "IO status (after read): "
              << static_cast<int>(bus.read(0xE0)) << '\n';

              std::cout << "\n";
    
    // viết dữ liệu vào trong ssd
    // để lưu trữ vĩnh viễn
    bus.write(0xF0, 0x05);
    bus.write(0xF1, 0x01);
    bus.write(0xF3, 77);

    bus.write(0xF0, 0x00);
    bus.write(0xF1, 0x00);
    std::cout << "SSD at 0x0000: "
              << static_cast<int>(bus.read(0xF2)) << '\n';

    bus.write(0xF0, 0x05);
    bus.write(0xF1, 0x01);
    std::cout << "SSD at 0x0105: "
              << static_cast<int>(bus.read(0xF2)) << '\n';

    std::cout << "\n";
    std::cout << "PC (initial): " << static_cast<int>(registers.get_pc()) << '\n';
    std::cout << "SP (initial): " << static_cast<int>(registers.get_sp()) << '\n';

    registers.set_pc(10);
    std::cout << "PC after set_pc(10): " << static_cast<int>(registers.get_pc()) << '\n';

    registers.increment_pc();
    std::cout << "PC after increment: " << static_cast<int>(registers.get_pc()) << '\n';

    registers.set_sp(200);
    std::cout << "SP after set_sp(200): " << static_cast<int>(registers.get_sp()) << '\n';

    Flags flags;
    flags.is_zero = true;
    flags.is_carry = false;
    flags.is_negative = true;
    registers.set_flags(flags);

    Flags read_flags = registers.get_flags();
    std::cout << "Zero: " << read_flags.is_zero
              << ", Carry: " << read_flags.is_carry
              << ", Negative: " << read_flags.is_negative << '\n';

    registers.set_pc(255);
    registers.increment_pc();
    std::cout << "PC after wraparound: " << static_cast<int>(registers.get_pc()) << '\n';

    return 0;
}

