/*
[13] Write a function that takes a vector<string> argument and returns a
vector<int> containing the number of characters in each string. Also find
the longest and the shortest string and the lexicographically first and last
string. How many separate functions would you use for these tasks?
Why?
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cout, std::vector, std::string;

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    os << "[";
    if (!vec.empty())
    {
        os << vec[0];
        for (size_t i = 1; i < vec.size(); ++i)
        {
            os << ", " << vec[i];
        }
    }
    os << "]";
    return os;
}

vector<int> char_num(const vector<string>& vec)
{
    vector<int> char_int_map;
    int string_char_total = 0;
    for (unsigned long int i = 0; i < vec.size(); ++i)
    {
        for (char x : vec[i])
        {
            ++string_char_total;
        }
        char_int_map.push_back(string_char_total);
        string_char_total = 0;
    }
    return char_int_map;
}

int main()
{
    vector<string> list = {"one", "three", "four", "numbers"};
    vector<int> list_nums = char_num(list);
    for (unsigned long int i = 0; i < list.size(); ++i)
    {
        cout << "(" << list[i] << " = " << list_nums[i] << " characters)\n";
    }
    return 0;
}


