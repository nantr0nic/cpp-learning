#include <iostream>
using namespace std;

int main()
{
    char op = '*';
    double val1 = 0;
    double val2 = 0;
    while (cin>>op>>val1>>val2)
    {
        if (op == '+')
        {
            cout << val1 + val2 << endl;
        }
        if (op == '-')
        {
            cout << val1 - val2 << endl;
        }
        if (op == '*')
        {
            cout << val1 * val2 << endl;
        }
        if (op == '/')
        {
            cout << val1 / val2 << endl;
        }
    }
    return 0;
}