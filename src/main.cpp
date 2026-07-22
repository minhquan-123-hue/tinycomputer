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


    REGISTERS REGISTERS;

    REGISTERS.set_a(15);
    REGISTERS.set_b(99);

    std::cout << "A = " << static_cast<int>(REGISTERS.get_a()) << '\n';
    std::cout << "B = " << static_cast<int>(REGISTERS.get_b()) << '\n';

    REGISTERS.set_a(200);
    REGISTERS.set_b(50);

    std::cout << "A = " << static_cast<int>(REGISTERS.get_a()) << '\n';
    std::cout << "B = " << static_cast<int>(REGISTERS.get_b()) << '\n';

    Bus bus;

    bus.write(0x10, 42);
    std::cout << "RAM via Bus: " << static_cast<int>(bus.read(0x10)) << '\n';

    bus.write(0xE5, 7);
    std::cout << "IO via Bus: " << static_cast<int>(bus.read(0xE5)) << '\n';

    bus.write(0xF3, 9);
    std::cout << "SSD via Bus: " << static_cast<int>(bus.read(0xF3)) << '\n';

    return 0;
}

