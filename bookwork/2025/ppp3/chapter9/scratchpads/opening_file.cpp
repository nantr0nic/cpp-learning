#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

int main()
{
    std::cout << "Please enter input file name: ";
    std::string iname;
    std::cin >> iname;
    /*
    ifstream = an istream for reading from a file
    ofstream = an ostream for writing to a file 
    fstream = an iostream that can read and write 
    */
    // Need to #include <fstream> for std::ifstream and ofstream etc.
    std::ifstream ist {iname};      // ist is an input stream for the file named name (iname)
    // ^^ opens the file of that name for reading
    if (!ist)
    {
        throw std::runtime_error("can't open input file \"" + iname + "\"");
    }
    ist.close();

    return 0;
}