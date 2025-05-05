#include <iostream>

int main()
{
    int birthyear = 1991;
    int age = 34;
    std::cout << "Dec: "<< birthyear << "\n";
    std::cout << "Hex: " << std::hex << birthyear << "\n";
    std::cout << "Octal: " << std::oct << birthyear << "\n";
    std::cout << "Dec: "<< std::dec << age << "\n";         // need std::dec to revert ostream back to decimal
    std::cout << "Hex: " << std::hex << age << "\n";
    std::cout << "Octal: " << std::oct << age << "\n";
    return 0;
}