#include <iostream>
#include <iomanip>
#include "lib/RAM.h"

int main()
{
    RAM ram;

    ram.write(0, 25);
    ram.write(1, 99);
    ram.write(2, 42);

    std::cout << "Address    Value\n";
    std::cout << "-------    -----\n";

    for (int address = 0; address < 256; address++)
    {
        std::cout << std::left
                  << std::setw(11) << address
                  << (int)ram.read(address)
                  << '\n';
    }

    return 0;
}