/*
Write a program that replaces punctuation with whitespace. Consider .
(dot), ; (semicolon), , (comma), ? (question mark), − (dash), ’ (single
quote) punctuation characters. Don’t modify characters within a pair of
double quotes ("). For example, “− don’t use the as−if rule.” becomes “don t
use the as if rule ”.
*/

#include <iostream>
#include <string>
#include <cctype>

int main()
{
    std::string line {};
    bool quotes {false};
    int quoteNum {};

    std::cout << "Write a line you want changed\n >> ";
    std::getline(std::cin, line);

    for (char& c : line)
    {
        if (c == '"')
        {
            quotes = !quotes;
            quoteNum++;
        }
        if (!quotes)
        {
            if (c == '"' && quoteNum % 2 == 0)
            {
                c = '"';
            }
            else if (ispunct(c))
            {
                c = ' ';
            }
        }
    }

    std::cout << line;

    return 0;
}