#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

using std::cout, std::cin, std::ifstream, std::string, std::vector;

bool isVowel(char c)
{
    c = static_cast<char>(tolower(c));
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

int main()
{
    // Get file name and open it etc
    string iname;
    cout << "Enter the name of a file to disemvowel: ";
    cin >> iname;

    ifstream ist {iname};

    if (!ist)
    {
        throw std::runtime_error("Couldn't open file: " + iname);
    }

    /*
    // Now the disemvoweling
    // this replaces the vowels with spaces
    string line;
    while (getline(ist, line))
    {
        for (char& c : line)
        {
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
            {
                c = ' ';
            }
        }
        cout << line << '\n';
    }
    */

    // Devowel by rebuilding the sentences with only consonants
    // Fix later...
    string line;
    string disemvoweled;
    while (getline(ist, line))
    {
        for (const char& c : line)
        {
            if (!isVowel(c))
            {
                disemvoweled += c;
            }
        }
        cout << disemvoweled << "\n";
    }

    return 0;
}