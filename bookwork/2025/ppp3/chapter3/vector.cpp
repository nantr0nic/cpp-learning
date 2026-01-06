// Vector and range-for-loop

#include <iostream>
#include <vector>

using std::cout, std::vector, std::string;

int main()
{
    vector<int> v = {5, 7, 9, 4, 6, 8};

    cout << "First loop! \n";
    for (long unsigned int i = 0; i < v.size(); ++i)
    {
        cout << v[i] << '\n';
    }

    cout << "Second loop using a 'range-for-loop'!\n";
    for (int x : v)
    {
        cout << x << '\n';
    }

    cout << "Range-for-loop with string vector.\n";
    vector<string> s = {"one", "two", "three"};
    for (string z : s)
    {
        cout << z << '\n';
    }
    cout << "Size of string vector is: " << s.size();

    return 0;
}

// range for a vector is [0:v.size()) --> "half-open sequence of elements"
// this is v[0] and v[v.size()-1]