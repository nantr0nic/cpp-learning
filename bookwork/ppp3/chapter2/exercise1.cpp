#include <iostream>
using namespace std;

int main()
{
    cout << "Give me a number of miles and I'll return kilometers.\n";
    double d = 0;
    while (cin>>d)
    {
        cout << "\nKilometers: " << (d * 1.609) << "\n";
    }
    return 0;
}