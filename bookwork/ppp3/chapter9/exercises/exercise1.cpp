#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

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
    for (char c; ist>>c; )
    {
        char d {tolower(c)};
        ost << d;
    }

    return 0;
}