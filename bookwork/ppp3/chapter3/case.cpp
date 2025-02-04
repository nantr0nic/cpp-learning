// some new stuff with switch
// can only use char, int, or enumeration type
// can group cases like so:

#include <iostream>
using namespace std;

int main()
{
    cout << "Enter a digit >> ";
    char a = 0;
    cin >> a;

    switch (a)
    {
        case '0': case '2': case '4': case '6': case '8':
            cout << "is even\n";
            // if want to... [[fallthrough]];
            break;
        case '1': case '3': case '5': case '7': case '9':
            cout << "is odd\n";
            break;
        default:
            cout << "is not a digit!\n";
            break;
    }
}