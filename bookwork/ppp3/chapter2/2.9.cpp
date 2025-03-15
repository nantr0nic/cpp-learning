// Demonstrates that C++ provides a way to convert certain types.

#include <iostream>

using namespace std;

int main()
{
    while (5 == 5)
    {
        cout << "Give me a character and I'll give you it's ASCII number.\n";
        cout << " >> ";
        char c;
        cin >> c;
        int i = c;
        cout << c << " is " << i << "\n";
    }
}