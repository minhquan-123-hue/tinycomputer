#include <iostream>
#include <iomanip>
#include "../lib/Bus.h"
#include "../lib/RAM.h"
#include "../lib/REGISTERS.h"

int main()
{
    // phần này sẽ có sự can thiệp của
    // CPU - RAM - I/O - SCREEN
    RAM ram;

    ram.write(0, 25);
    ram.write(1, 99);
    ram.write(2, 42);

    std::cout << "Address    Value\n";
    std::cout << "-------    -----\n";

    for (int address = 0; address < 3; address++)
    {
        std::cout << std::left
                  << std::setw(11) << address
                  << (int)ram.read(address)
                  << "\n";
    }
    std::cout << "\n";


    REGISTERS registers;

    registers.set_a(15);
    registers.set_b(99);

    std::cout << "A = " << static_cast<int>(registers.get_a()) << '\n';
    std::cout << "B = " << static_cast<int>(registers.get_b()) << "\n\n";


    Bus bus;

    bus.write(0xE2, 'H');
    bus.write(0xE2, 'i');
    bus.write(0xE2, '\n');

    std::cout << "IO status (before key): "
              << static_cast<int>(bus.read(0xE0)) << '\n';

    bus.get_io_unit().push_key_input('X');

    std::cout << "IO status (after key): "
              << static_cast<int>(bus.read(0xE0)) << '\n';
    std::cout << "IO key data: "
              << static_cast<int>(bus.read(0xE1)) << '\n';
    std::cout << "IO status (after read): "
              << static_cast<int>(bus.read(0xE0)) << '\n';

              std::cout << "\n";
              
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

