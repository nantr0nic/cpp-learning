//$ ----- Exercise 11 -----//
// Rewrite palindrome exercises to flip word then compare letters.

#include <cstring>
#include <iostream>
#include <string>
#include <print>

// std::string arguments
bool is_palindrome_string(const std::string& s)
{
    std::string sBack;
    for (size_t i = s.size(); i > 0; --i)
        sBack.push_back(s[i - 1]);
    for (size_t i = 0; i < s.size(); ++i)
        if (s[i] != sBack[i])
            return false;
    return true;
}

bool is_palindrome_string2(const std::string& s)
{
    for (auto front = s.begin(), back = s.end() - 1;
    front != s.end() && back != s.begin();
    ++front, --back)
    {
        if (*front != *back)
            return false;
    }
    return true;
}

// c-style strings
bool is_palindrome_a(const char s[])
{
    size_t sSize {strlen(s)};
    // #12
    if (sSize >= 16)
    {
        std::println("{} is too long! Returning FALSE.", s);
        return false;;
    }

    char* sCopy {new char[sSize + 1]};
    for (size_t i = sSize, j = 0; i > 0; --i, ++j)
    {
        sCopy[j] = s[i-1];
    }
    // make sure to add the terminator!
    sCopy[sSize] = '\0';
    for (size_t i = 0; i < sSize; ++i)
        if (sCopy[i] != s[i])
        {
            delete[] sCopy;
            return false;
        }
    delete[] sCopy;
    return true;
}

bool is_palindrome_a2(const char* s)
{
    size_t sSize {strlen(s)};
    char* sCopy = (char*)malloc(sSize + 1);
    for (size_t i = 0; i < sSize; ++i)
    {
        sCopy[i] = s[sSize - 1 - i];
    }
    // make sure to add the terminator!
    sCopy[sSize] = '\0';
    bool result{strcmp(s, sCopy) == 0};

    free(sCopy);
    return result;
}

int main()
{
    std::println("home (string): {}", is_palindrome_string("home"));
    std::println("madam (string): {}", is_palindrome_string("madam"));
    std::println("home (string2): {}", is_palindrome_string2("home"));
    std::println("madam (string2): {}", is_palindrome_string2("madam"));
    
    char home[] = "home";
    char madam[] = "madam";
    std::println("home (array): {}", is_palindrome_a(home));
    std::println("madam (array): {}", is_palindrome_a(madam));
    std::println("home (array2): {}", is_palindrome_a2(home));
    std::println("madam (array2): {}", is_palindrome_a2(madam));

    constexpr size_t bufferSize = 50;
    char input[bufferSize];
    std::println("Enter a word! (Ctrl + D to exit)");
    while (std::cin >> input)
    {
    std::println("Enter a word! (Ctrl + D to exit)");
    std::println("Is {} a palindrome? {}!", input, is_palindrome_a(input));
    }

    return 0;
}