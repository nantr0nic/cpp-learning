// using 'auto' type deduction

#include <iostream>
#include <typeinfo>

using namespace std;

int main()
{
    auto x = 7;
    auto d = 7.7;
    cout << "x is " << x << "\n";
    cout << "d is " << d << "\n";
    cout << "x is type " << typeid(x).name() << "\n";
    cout << "d is type " << typeid(d).name() << "\n";
    return 0;
}
