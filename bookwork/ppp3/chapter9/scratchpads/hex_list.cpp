#include <iostream>

int main()
{
    for (int i = 1024; i < 2050; ++i)
    {
        std::cout << "#" << std::dec << i << " = 0x" << std::hex << i << "\n";
    }
    return 0;
}