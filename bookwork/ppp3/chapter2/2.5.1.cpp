#include <iostream>
using namespace std;

int main()
{
    string previous;
    string current;
    int x = 2;
    int b = x+5;
    while (cin>>current)
    {
        if (previous == current)
        {
            cout << "repeated word: " << current << "\n";
        }
        previous = current;
        cout << b;
    }
}