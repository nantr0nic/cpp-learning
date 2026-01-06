/*
Write a program that reads strings and for each string outputs the
character classification of each character, as defined by the character
classification functions presented in §9.10.3. Note that a character can
have several classifications (e.g., x is both a letter and an alphanumeric).
*/

#include <iostream>
#include <cctype>
#include <string>

int main()
{
    std::string line {};
    std::cout << "What line would you like analyzed? \n >> ";
    std::getline(std::cin, line);

    for (const char& c : line)
    {
        std::cout << "Character \'" << c << "\' is...\n";
        if (isspace(c))
        {
            std::cout << " -> a whitespace! (isspace())\n";
        }
        if (isalpha(c))
        {
            std::cout << " -> a letter! (isalpha())\n";
        }
        if (isdigit(c))
        {
            std::cout << " -> a decimal digit! (isdigit())\n";
        }
        if (isxdigit(c))
        {
            std::cout << " -> a hexadecimal digit! (isxdigit())\n";
        }
        if (isupper(c))
        {
            std::cout << " -> an uppercase letter! (isupper())\n";
        }
        if (islower(c))
        {
            std::cout << " -> a lowercase letter! (islower())\n";
        }
        if (isalnum(c))
        {
            std::cout << " -> alphanumeric, a letter or a decimal digit! (isalnum())\n";
        }
        if (iscntrl(c))
        {
            std::cout << " -> a control character! (iscntrl())\n";
        }
        if (ispunct(c))
        {
            std::cout << " -> punctuation! (ispunct())\n";
        }
        if (isprint(c))
        {
            std::cout << " -> printable! (isprint())\n";
        }
        if (isgraph(c))
        {
            std::cout << " -> alpha, digit, or punct... (isgraph())\n";
        }
    }

    return 0;
}
