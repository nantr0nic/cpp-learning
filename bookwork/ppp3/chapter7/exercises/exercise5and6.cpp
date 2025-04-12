/*
Write two functions that reverse the order of elements in a vector<int>.
For example, 1, 3, 5, 7, 9 becomes 9, 7, 5, 3, 1. 
The first reverse function should produce a new vector with the reversed sequence,
leaving its original vector unchanged. 
The other reverse function should reverse the elements of its vector 
without using any other vectors (hint: swap).

Exercise 6: Write versions of the functions from exercise 5, but with a vector<string>.
*/

#include <iostream>
#include <vector>
#include <string>

using std::cout, std::vector, std::string;

auto vec_reverse1(const vector<int>& vec) -> vector<int>;
void vec_reverse2(vector<int>& vec);
auto vec_string_rev1(const vector<string>& vec) -> vector<string>;
void vec_string_rev2(vector<string>& vec);
std::ostream& operator<<(std::ostream& os, const vector<int>& vec);
std::ostream& operator<<(std::ostream& os, const vector<string>& vec);

int main()
{
    vector<int> vec {1, 3, 5, 7, 9};
    cout << "Original vector: " << vec << "\n";
    vector<int> new_vec = vec_reverse1(vec);
    cout << "New vector (vec_reverse1): " << new_vec << "\n";
    vec_reverse2(vec);
    cout << "Original vector rev (vec_reverse2): " << vec << std::endl;

    cout << "-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << "\n";

    vector<string> vec_string {"Sword", "Shield", "Bow", "Quiver"};
    cout << "Original string vector: " << vec_string << "\n";
    vector<string> new_string_vec = vec_string_rev1(vec_string);
    cout << "New string vector (vec_string_rev1): " << new_string_vec << "\n";
    vec_string_rev2(vec_string);
    cout << "Original string vector rev (vec_string_rev2): " << vec_string << std::endl;
    return 0;
}

// Return a new vector<int> that's the reverse of a vector<int>
auto vec_reverse1(const vector<int>& vec) -> vector<int>     // just for fun lol
{
    vector<int> new_vec;
    long unsigned int i = vec.size();
    while (i > 0)
    {
        --i;
        new_vec.push_back(vec[i]);
    }
    return new_vec;
}

// Reverse a vector<int>
void vec_reverse2(vector<int>& vec)
{
    int temp = 0;
    for (long unsigned int i = 0; i < vec.size() / 2; ++i)
    {
        temp = vec[i];
        vec[i] = vec[(vec.size() - 1) - i];
        vec[(vec.size() - 1) - i] = temp;
    }
}

// Return a new vector<string> that's the reverse of a vector<string>
auto vec_string_rev1(const vector<string>& vec) -> vector<string>
{
    vector<string> new_vec;
    long unsigned int i = vec.size();
    while (i > 0)
    {
        --i;
        new_vec.push_back(vec[i]);
    }
    return new_vec;
}

// Reverse a vector<string>
void vec_string_rev2(vector<string>& vec)
{
    string temp = "";
    for (long unsigned int i = 0; i < vec.size() / 2; ++i)
    {
        temp = vec[i];
        vec[i] = vec[(vec.size() - 1) - i];
        vec[(vec.size() - 1) - i] = temp;
    }
}

// Overload << for vector<int>
std::ostream& operator<<(std::ostream& os, const vector<int>& vec)
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

// Overload << for vector<string>
std::ostream& operator<<(std::ostream& os, const vector<string>& vec)
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
