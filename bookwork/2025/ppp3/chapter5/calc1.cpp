#include <iostream>

using std::cout, std::cin;

int main()
{
    cout << "Please enter expression (we can handle + and -): ";
    int lval = 0;
    int rval = 0;
    char op = 0;
    int res = 0;
    cin >> lval >> op >> rval;          // read something like 1 + 3

    if (op=='+')
        res = lval + rval;
    else if (op=='-')
        res = lval - rval;
    cout << "Result: " << res << '\n';

    return 0;
}