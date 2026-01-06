#include <iostream>
#include <fstream>
#include <vector>
#include <ios>

void fill_vector(std::istream& ist, std::vector<int>& v, char terminator)
// read integers from ist into v until we reach eof() or terminator
{
    ist.exceptions(ist.exceptions()|std::ios::badbit);  // make ist throw if it goes bad
    // ist.exceptions(ist.exceptions()|ios::badbit|ios::failbit); // throw on any failure
    for (int x; ist>>x; )
        v.push_back(x);
    if (ist.eof())                              // fine: we found the end of file
        return;
    /*
    // The following isn't necessary because if ist.exceptions() line at the top
        if (ist.bad())                              // stream corrupted;
        throw std::runtime_error("ist is bad"); // let's get out of here!
    if (ist.fail())                             // clean up the mess as best we can
    {
        ist.clear();                            // clear stream state
        char c = 0;
        ist >> c;                               // read a character, hopefully terminator
        if (c != terminator)                    // unexpected character
        {
            ist.unget();                        // put that character back
            ist.clear(std::ios::failbit);       // set the state to fail()
        }
    }
    */

    // If we get here then ist not good(), bad(), nor eof() so ist must be fail()
    ist.clear();
    char c = 0;
    ist >> c;
    if (c != terminator)
    {
        ist.unget();
        ist.clear(std::ios::failbit);
    }
}