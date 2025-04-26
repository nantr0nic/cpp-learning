#include <iostream>
#include <string>
#include <fstream>

using std::cout, std::string, std::cin, std::ofstream;

int main()
{
    cout << "Please enter name of output file: ";
    string oname;
    cin >> oname;
    ofstream ost {oname};   // ost is an output stream for a file named oname
    if (!ost)
        throw std::runtime_error("can't open output file " + oname);
        // I think this would be thrown if binary doesn't have proper permissions

    return 0;
}