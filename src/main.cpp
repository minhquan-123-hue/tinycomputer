#include <iostream>
#include <iomanip>
#include "../lib/Bus.h"
#include "../lib/RAM.h"
#include "../lib/REGISTERS.h"

int main()
{
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
                  << '\n';
    }


    REGISTERS registers;

    registers.set_a(15);
    registers.set_b(99);

    std::cout << "A = " << static_cast<int>(registers.get_a()) << '\n';
    std::cout << "B = " << static_cast<int>(registers.get_b()) << '\n';

    registers.set_a(200);
    registers.set_b(50);

    std::cout << "A = " << static_cast<int>(registers.get_a()) << '\n';
    std::cout << "B = " << static_cast<int>(registers.get_b()) << '\n';

    Bus bus;

    bus.write(0x10, 42);
    std::cout << "RAM via Bus: " << static_cast<int>(bus.read(0x10)) << '\n';

    bus.write(0xE5, 7);
    std::cout << "IO via Bus: " << static_cast<int>(bus.read(0xE5)) << '\n';

    bus.write(0xF3, 9);
    std::cout << "SSD via Bus: " << static_cast<int>(bus.read(0xF3)) << '\n';

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

    return 0;
}

