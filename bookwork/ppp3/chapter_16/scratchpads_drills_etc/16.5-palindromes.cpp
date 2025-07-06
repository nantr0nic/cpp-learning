//$ ----- 16.5 Palindromes ----- //

// #define _GLIBCXX_USE_DEPRECATED 1
#include <iostream>
#include <string>
#include <cstring>

// Palindromes using string
bool is_palindrome(const std::string& s)
{
    size_t first = 0;               // index of first letter
    size_t last = s.length() - 1;   // index of last letter
    while (first < last)            // we haven't reached the middle
    {
        if (s[first] != s[last])
            return false;
        ++first;                    // move forward
        --last;                     // move backward
    }
    return true;
}

// Palindromes using arrays

// My compiler won't let me write read_word as it is written in the book.
// I tried enabling the deprecated use flag but still no luck. Guess I won't
// be able to use the examples that require read_word()

bool is_palindrome(const char s[], int n)
// s points to the first character of an array of n characters
{
    int first = 0;
    int last = n-1;
    while (first < last)
    {
        if (s[first] != s[last])
            return false;
        ++first;
        --last;
    }
    return true;
}

// To exercise the above function, we first have to get characters read into the array.
// One way to do that without risk of overflowing the array is like this:

// std::istream& read_word(std::istream& is, char* buffer, int max)
// // read at most max-1 characters from is into buffer
// {
//     is.width(max);
//     // my compiler won't allow the statement below...
//     is >> buffer;
//     return is;
// }

// Palindromes using pointers

bool is_palindrome(const char* first, const char* last)
// first points to the first letter, last to the last letter
{
    while (first < last)
    {
        if (*first != *last)
            return false;
        ++first;
        --last;
    }
    return true;
}

bool is_palindrome_recursive(const char* first, const char* last)
{
    if (first < last)
        return (*first == *last) ? is_palindrome_recursive(first+1, last-1) : false;
    return true;
}

// Palindromes using span

bool is_palindrome(std::span<char> s)
{
    return (s.size()) ? is_palindrome(s.data(), s.data() + s.size()) : true;
}

bool is_palindrome_s(std::span<char> s)
{
    if (s.size() < 2)
        return true;
    return (s.front() == s.back()) ? is_palindrome(std::span<char>{s.data()+1,s.size()-2}) : false;
    
}

int main()
{
    // using string
    for (std::string s; std::cin>>s; )
    {
        std::cout << s << " is ";
        if (!is_palindrome(s))
            std::cout << "not ";
        std::cout << "a palindrome\n";
    }


    return 0;
}