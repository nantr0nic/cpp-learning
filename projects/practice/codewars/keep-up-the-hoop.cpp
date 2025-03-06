#include <iostream>

using namespace std;

int main()
{
    int times = 0;
    cout << "Alex, how many times did the hoop go round?\n >> ";
    cin >> times;
    if (times < 10)
    {
        cout << "Keep at it until you get it\n";
    }
    if (times >= 10)
    {
        cout << "Great, now move on to tricks\n";
    }
    return 0;
}

/*
#include <string>
std::string hoop_count(unsigned n) {
   return (n >= 10) ? "Great, now move on to tricks" : "Keep at it until you get it";
}

^^^ The ?: thing is called a 'ternary operator'

condition ? expression1 : expression2
If condition is true, expression1 is executed.
If condition is false, expression2 is executed.
*/