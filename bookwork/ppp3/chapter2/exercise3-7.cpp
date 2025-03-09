//////// First way using only <string> /////////
/*

#include <iostream>
#include <string>

using std::cin, std::cout, std::string;

int main()
{
    string a{""}, b{""}, c{""}, temp{""};
    cout << "Enter three words (case sensitive...)\n";
    cout << "1) ";
    cin >> a;
    cout << "2) ";
    cin >> b;
    cout << "3) ";
    cin >> c;
    if (a > b)
    {
        temp = a;
        a = b;
        b = temp;
    }
    if (a > c)
    {
        temp = a;
        a = c;
        c = temp;
    }
    if (b > c)
    {
        temp = b;
        b = c;
        c = temp;
    }

    cout << a << ", " << b << ", " << c << std::endl;
    return 0;
}

*/

////////// Second way using string, vector, and std::sort //////////////
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

using std::cin, std::cout;

int main()
{
    std::vector<std::string> words(3, "");
    cout << "Enter three words\n(a) >> ";
    cin >> words[0];
    cout << "(b) >> ";
    cin >> words[1];
    cout << "(c) >> ";
    cin >> words[2];

    std::sort(words.begin(), words.end());

    cout << words[0] << ", " << words[1] << ", " << words[2] << std::endl;
    return 0;
}