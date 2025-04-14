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

// Declarations
template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec);

vector<size_t> char_num(const vector<string>& vec);
void max_min_strings(const vector<string>& list, const vector<size_t>& list_nums);
void print_sorted_strings(const vector<string>& list);

// Main
int main()
{
    vector<string> list = {"This", "is", "a", "test", "sentence", "woot!"};
    vector<size_t> list_nums = char_num(list);

    cout << "This is a test sentence woot!\n";

    // Print the character lengths of each item in 'list'
    for (size_t i = 0; i < list.size(); ++i)
    {
        cout << "(" << list[i] << " = " << list_nums[i] << " characters)\n";
    }

    cout << "\n";

    max_min_strings(list, list_nums);
    print_sorted_strings(list);

    return 0;
}

// Template for overloading the << operator to print vectors of any type.
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

// Returns a vector of character lengths for a vector of strings.
vector<size_t> char_num(const vector<string>& vec)
{
    vector<size_t> char_int_map;
    for (const string& s : vec)
    {
        char_int_map.push_back(s.size());
    }
    return char_int_map;
}

// Find the longest and shortest strings.
void max_min_strings(const vector<string>& list, const vector<size_t>& list_nums)
{
    if (list.empty() || list_nums.empty())
    {
        cout << "The list is empty.\n";
        return;
    }

    size_t longest_index = 0;
    size_t shortest_index = 0;

    for (size_t i = 1; i < list_nums.size(); ++i)
    {
        if (list_nums[i] > list_nums[longest_index])
        {
            longest_index = i;
        }
        if (list_nums[i] < list_nums[shortest_index])
        {
            shortest_index = i;
        }
    }

    cout << "The longest string is \"" << list[longest_index] << "\" with " 
        << list_nums[longest_index] << " characters.\n";
    cout << "The shortest string is \"" << list[shortest_index] << "\" with " 
        << list_nums[shortest_index] << " characters.\n";
}

// Print an alphabetically sorted list with character lengths.
void print_sorted_strings(const vector<string>& list)
{
    // Make a copy of the list; goal is to NOT modify the original list.
    vector<string> list_sorted = list;
    // Sort the string list alphabetically
    std::sort(list_sorted.begin(), list_sorted.end());
    vector<size_t> list_sorted_nums = char_num(list_sorted);

    cout << "\nHere is the list sorted alphabetically.\n";
    for (size_t i = 0; i < list_sorted.size(); ++i)
    {
        cout << "(" << list_sorted[i] << " = " << list_sorted_nums[i] << " characters)\n";
    }
}