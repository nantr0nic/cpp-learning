#include <iostream>

using std::cout;

int round_to(const double x)
{
    // this also doubles (no pun intended) as a conversion from double to int
    int y = x;
    return ((x - 0.49999) < y) ? y : y + 1;
}

void ascii_map(const int x)
{
    for (int i = 33; i < x; ++i)
    {
        char y = i;
        cout << i << " = " << y << "\n";
    }
}

double conv1(const int x) { return double(x); }

int main()
{
    double one = 7.1;
    double two = 7.8;
    cout << "--- Rounding function test ---" << "\n";
    cout << "7.1 --> " << round_to(one) << "\n";
    cout << "7.8 --> " << round_to(two) << "\n";
    cout << "3.05 --> " << round_to(3.05) << "\n";
    cout << "5.49 --> " << round_to(5.49) << "\n";
    cout << "4.5 --> " << round_to(4.5) << "\n";
    cout << "4.501 --> " << round_to(4.501) << "\n";

    int a = 65;
    cout << "Conv1 [int to double]" << "\n";
    cout << conv1(a) << "\n";
    cout << conv1(1001) << "\n";

    char x = a;
    cout << x << "\n";

    cout << "ASCII map going from 33 to 128" << "\n";
    ascii_map(128);

    return 0;
}