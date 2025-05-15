#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>
#include <cctype>

using std::cin, std::cout, std::string;

int main()
{
    cout << "Please enter a file name that you want converted to lower-case\n >> ";
    string iname;
    cin >> iname;

    std::ifstream ist {iname};
    if (!ist)
    {
        throw std::runtime_error("can't open input file \"" + iname + "\"");
    }

    std::ofstream ost {"output.txt"};
    if (!ost)
    {
        throw std::runtime_error("can't open output file\n");
    }

    ist >> std::noskipws;
    for (char c; ist>>c; )
    {
        //char d {tolower(c)};
        //^^ this causes a narrowing conversion warning. Proper use is to cast:
        char d {static_cast<char>(tolower(c))};
        ost << d;
    }

    return 0;
}