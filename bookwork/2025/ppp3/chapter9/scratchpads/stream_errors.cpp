#include <iostream>

using namespace std;

int main()
{
    int i = 0;
    cin >> i;
    if (!cin)           // we get here (only) if an input operation failed
    {
        if (cin.bad())  // stream corrupted
            throw std::runtime_error("cin is bad"); // get out of it!
        if (cin.eof())  // no more input:
        {
            // ... this is often how we want a sequence of input operations to end ...
        }
        if (cin.fail()) // stream encountered something unexpected
        {
            cin.clear(); // make ready for more input
            // ... somehow recover
        }
    }

    return 0;
}