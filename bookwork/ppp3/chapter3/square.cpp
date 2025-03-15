// Try this: make a square function without using the multiplication operator

#include <iostream>

using std::cin, std::cout;

int square(int x)
{
    int j = 0;
    for (int i = 0; i < x; ++i)
    {
        j += x;
    }
    return j;
}

int main()
{
    int x = 0;
    cout << "Enter a digit >> ";
    cin >> x;
    cout << "Squared: " << square(x);
    return 0;
}