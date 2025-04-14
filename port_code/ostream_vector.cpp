#include <iostream>
#include <vector>

std::ostream& operator<<(std::ostream& os, const std::vector<int>& vec)
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

// Template below...

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

/* 
// A version of the template using a range-based for loop instead of an index-based one.

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    os << "[";
    bool first = true;
    for (const auto& element : vec)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            os << ", ";
        }
        os << element;
    }
    os << "]";
    return os;
}

*/

// Auto'd... I don't think this works.
/*
std::ostream& operator<<(std::ostream& os, const std::vector<auto>& vec)
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
*/