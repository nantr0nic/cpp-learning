#include <iostream>
using namespace std;

int main()
{
    double d = 0;
    int x0 = 7.8;   // narrows, some compilers warn
    // the following two initializations don't narrow and so won't compile
    //int x1 {7.8};   // error: {} doesn't narrow
    //int x2 = {7.8}; // error: ={} doesn't narrow
    int x3 (7.8);   // narrows, some compilers warn
    cout << "test d:" << d << "\n";
    cout << "x0: " << x0 << " / x3: " << x3 << "\n";
    while (cin>>d)
    {
        int i = d;
        char c = i;
        cout << "d==" << d
            << " i==" << i
            << " c==" << c
            << " char(" << c << ")\n";
    }
    return 0;
}