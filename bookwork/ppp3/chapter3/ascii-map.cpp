// using while to write out the ascii map

#include <iostream>

using namespace std;

int main()
{
    int i = 65;
    while (i < 123)
    {
        char c = i;
        cout << "Character: " << c << " / Number: " << i << "\n";
        ++i;
    }

    for (i = 65; i < 123; ++i)
    {
        char c = i;
        cout << "Character: " << c << " / Number: " << i << "\n";
    }
    return 0;
}