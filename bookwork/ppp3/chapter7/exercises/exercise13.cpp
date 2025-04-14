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

vector<int> char_num(const vector<string>& vec);
void max_min_strings(const vector<string>& list, const vector<int>& list_nums);
// void print_sorted_strings(vector<string> list, const vector<int>& list_nums);
void print_sorted_strings_2(const vector<string>& list);

// Main
int main()
{
    vector<string> list = {"this", "is", "a", "test", "sentence", ",", "woot!"};
    vector<int> list_nums = char_num(list);
    for (size_t i = 0; i < list.size(); ++i)
    {
        cout << "(" << list[i] << " = " << list_nums[i] << " characters)\n";
    }

    max_min_strings(list, list_nums);
    // print_sorted_strings(list, list_nums);
    print_sorted_strings_2(list);

    cout << "Size test\n" << list[0] << " is " << list[0].size() << " characters.\n";
    return 0;
}

// Template for overloading the << operator to print vectors.
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

// std::string has a built-in .size() function to return string lengths.
// For educational purposes, however, I wrote the bottom function.
vector<int> char_num(const vector<string>& vec)
{
    vector<int> char_int_map;
    int string_char_total = 0;
    for (const auto& str : vec)
    {
        // I used 'const char& x' but the compiler gave me an unused variable warning.
        // I replaced 'x' with '_' which is called an 'anonymous variable' instead.
        for (const char& _ : str)
        {
            ++string_char_total;
        }
        char_int_map.push_back(string_char_total);
        string_char_total = 0;  // reset total back to 0 before re-looping to next string
    }
    return char_int_map;
}

/*
/// Here is a version of the function using the built-in .size() function ///
// To deal with the conversion warning from long unsigned int to int (because of .size())
//      the vector must be of long unsigned int type.
//          OR size_t (which is now preferred)
vector<size_t> char_num(const vector<string>& vec)
{
    vector<size_t> char_int_map;
    for (const string& s : vec)
    {
        char_int_map.push_back(s.size()); // This gives a conversion warning.
    }
    return char_int_map;
}
*/

// Find the longest and shortest strings.
void max_min_strings(const vector<string>& list, const vector<int>& list_nums)
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

/*
// Print the string list in its alphabetical order.
void print_sorted_strings(vector<string> list, const vector<int>& list_nums)
{
    vector<string> list_presort = list;
    vector<int> list_nums_sorted;
    // Sort the string list alphabetically
    std::sort(list.begin(), list.end());

    // Sort the character length list to match the alphabetically sorted list
    for (size_t i = 0; i < list.size(); ++i)
    {
        for (size_t j = 0; j < list_presort.size(); ++j)
        {
            if (list_presort[j] == list[i])
            {
                list_nums_sorted.push_back(list_nums[j]);
                break;
            }
        }
    }
    cout << "\n Here is the list sorted alphabetically.\n";
    for (size_t i = 0; i < list.size(); ++i)
    {
        cout << "(" << list[i] << " = " << list_nums_sorted[i] << " characters)\n";
    }
}
*/ 

// A better version of the previous function because we can use char_num instead
//      of sorting the list_nums.
void print_sorted_strings_2(const vector<string>& list)
{
    vector<string> list_sorted = list;
    // Sort the string list alphabetically
    std::sort(list_sorted.begin(), list_sorted.end());
    vector<int> list_sorted_nums = char_num(list_sorted);

    cout << "\n Here is the list sorted alphabetically. (version 2)\n";
    for (size_t i = 0; i < list_sorted.size(); ++i)
    {
        cout << "(" << list_sorted[i] << " = " << list_sorted_nums[i] << " characters)\n";
    }
}