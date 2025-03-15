#include <iostream>
#include <vector>

using namespace std;

vector<int> countbyx(int x, int n)
{
    vector<int> numbers(n, 0);
    for (int i = 0; i < n; ++i)
    {
        numbers[i] = x * (i + 1);
    }
    return numbers;
}

// C++ doesn't have a built-in way to directly output a vector using cout.

ostream& operator<<(ostream& os, const vector<int>& vec)
{
    os << "[";
    for (size_t i = 0; i < vec.size(); ++i)
    {
        os << vec[i];
        if (i < vec.size() - 1) os << ", ";
    }
    os << "]";
    return os;
}

int main()
{
    int multiplesof = 0;
    int multiplesnum = 0;
    cout << "Enter the number you want multiples of >> ";
    cin >> multiplesof;
    cout << "How many multiples do you want >> ";
    cin >> multiplesnum;
    cout << "\nHere you go!\n";
    cout << countbyx(multiplesof, multiplesnum) << endl;
    return 0;
}