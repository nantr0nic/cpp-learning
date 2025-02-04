// constexpr vs const (for variables, not functions [yet])

#include <iostream>
using namespace std;

int main()
{
    constexpr int max = 100;
    int n;
    cout << "Enter an integer >> ";
    cin >> n;

    constexpr int c1 = max + 7; // Ok
    // constexpr int c2 = n + 7;   // Error. Must know value of N at compile time.
    const int c2 = n + 7;       // Ok -- const works for values determined at runtime.
                                // doesn't need to be known at compile time!
    cout << "constexpr max + 7 is: " << c1 << "\n";
    cout << "c2 is: " << c2 << endl;

    // c2 = 9                   // Error. Cannot change const.

    return 0;
}

