#include  <iostream>
#include <string>

using std::cin, std::cout, std::string;

int main()
{
    string input;

    cout << "Enter a string\n >> ";
    cin >> input;
    for (char c : input)
    {
        int i = c;
        cout << c << " --> " << i << "\n";
    }
    return 0;
}