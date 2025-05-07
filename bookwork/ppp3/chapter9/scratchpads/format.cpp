#include <iostream>
#include <cstdio>
#include <format>

int main()
{
    // C printf function:
    printf("An int %d and a string '%s'\n", 123, "Hello, World!");

    // format()
    std::string val = "World";
    std::string s = std::format("Hello, {}!", val);
    std::cout << s << "\n";
    int val2 = 1337;
    std::cout << std::format("Hello, {}!\n", val2);

    // various formatters
    int x = 1234;
    std::cout << std::format("{} - {:x} - {:o} - {:d} - {:b} - {}\n", x, x, x, x, x, x);
    /*
    x - hexadecimal
    o - octal
    d - decimal 
    b - binary 
    none - empty (for 'int', just d)
    For a complete listing...
    https://en.cppreference.com/w/cpp/utility/format/formatter
    */

    // For floating-point numbers
    constexpr double d = 1234.56789;
    std::cout << std::format("format: {} - {:a} - {:e} - {:f} - {:g}\n", d, d, d, d, d);
    /*
    a - hexfloat
    e - scientific
    f - fixed
    g - general, with precision 6
    none - general, with default precision
    */

    // character positions for width
    std::cout << std::format("width: {} - {:8} - {:20} - \n", d, d, d);

    // precision is specified by a number after a dot
    std::cout << std::format("precision: {} - {:.8} - {:.20} - \n", d, d, d);

    // You can combine formatting directives
    std::cout << std::format("combining... - {:12} - {:12.8f} - {:30.20e} - \n", d, d, d);

    return 0;
}