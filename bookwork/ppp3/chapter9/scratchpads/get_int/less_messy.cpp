#include <iostream>

using namespace std;

void skip_to_int()
{
    if (cin.fail())
    {
        cin.clear();
        for (char ch; cin>>ch; )
        {
            if (isdigit(ch) || ch=='-')
            {
                cin.unget();
                return;
            }
        }
    }
    throw std::runtime_error("no input");
}

int get10()
{
    cout << "Please enter an integer in the range 1 to 10 (inclusive):\n";
    int n = 0;
    while (true) 
    {
        if (cin>>n) 
        {
        // we got an integer; now check it
            if (1<=n && n<=10)
                return n;
            cout << "Sorry " << n << " is not in the [1:10] range; please try again\n";
        }
        else 
        {
            cout << "Sorry, that was not a number; please try again\n";
            skip_to_int();
        }
    }
}