#include <iostream>
#include <format>

using std::cout, std::cin, std::format;

int main()
{
    int birth_year = 1991;

    // Output in decimal, hexadecimal, and octal form
    // First method
    cout << "Birth year: 1991\n";
    cout << "Dec:\t" << std::dec << birth_year << "\t Base 10\n";
    cout << "Hex:\t" << std::hex << birth_year << "\t Base 16\n";
    cout << "Oct:\t" << std::oct << birth_year << "\t Base 8\n";
    cout << "My (current) age: " << std::dec << 34 << "\n";

    cout << "\n<<Exercise 8>>\n";
    int a {};
    int b {};
    int c {};
    int d {};
    cout << " >> ";
    cin >> a >> std::oct >> b >> std::hex >> c >> d;
    cout << a << '\t' << b << '\t' << c << '\t' << d << '\n';

    /*
    Explaining the results "1234    668    4660    4660"
    a is read in as the 'int' default decimal,
    b is read in as an octal,
    c is read in as hexadecimal and because the istream isn't
    reverted back to decimal, d is read in as hexadecimal as well.

    The local variables are stored in those bases, meaning
    the value of c and d is '4660', not '1234'.
    */
    
    return 0;
}
