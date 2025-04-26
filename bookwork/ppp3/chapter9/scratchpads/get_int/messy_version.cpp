#include <iostream>

using namespace std;

int get10()
{
    cout << "Please enter an integer in the range 1 to 10 (inclusive):\n";
    int n {};
    while (true)
    {
        cin >> n;
        if (cin)                    // we got an inteer; now check it
        {
            if (1 <=n && n <=10)
            {
                return n;
            }
            cout << "Sorry " << n << " is not in the [1:10] range; please try again!\n";
        }
        else if (cin.fail())        // we found something that wasn't an integer
        {
            cin.clear();            // set the state back to good() we want to look
            cout << "Sorry, that was not a number; please try again!\n";
            for (char ch; cin>>ch && !isdigit(ch); )    // throw away non-digit
                /* Nothing */ ;
            if (!cin)               // we didn't find a digit: give up
                throw std::runtime_error("no input");
            cin.unget();            // put the digit back, so that we can read...
        }
        else
            throw std::runtime_error("no input");   // bad: give up
    }
}

int main()
{
    get10();
    return 0;
}