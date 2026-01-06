/*
Write a program that reads a text file and writes out how many
characters of each character classification (§9.10.3) are in the file.
*/

// Doesn't count spaces correctly, but otherwise works.

#include <iostream>
#include <cctype>
#include <string>
#include <fstream>
#include <vector>

std::vector<std::string> parseWords(std::ifstream& ist);

int main()
{
    std::string fileName {};
    std::cout << "What file would you like analyzed? \n >> ";
    std::cin >> fileName;
    std::ifstream ist {fileName};
    std::vector<std::string> words {parseWords(ist)};

    unsigned int space {};
    unsigned int alpha {};
    unsigned int digit {};
    unsigned int xdigit {};
    unsigned int uppercase {};
    unsigned int lowercase {};
    unsigned int alnum {};
    unsigned int cntrl {};
    unsigned int punct {};
    unsigned int printable {};
    unsigned int graph {};

    for (const std::string& string : words)
    {
        for (const char& c : string)
        {
            if (isspace(c))
            {
                space++;
            }
            if (isalpha(c))
            {
                alpha++;
            }
            if (isdigit(c))
            {
                digit++;
            }
            if (isxdigit(c))
            {
                xdigit++;
            }
            if (isupper(c))
            {
                uppercase++;
            }
            if (islower(c))
            {
                lowercase++;
            }
            if (isalnum(c))
            {
                alnum++;
            }
            if (iscntrl(c))
            {
                cntrl++;
            }
            if (ispunct(c))
            {
                punct++;
            }
            if (isprint(c))
            {
                printable++;
            }
            if (isgraph(c))
            {
                graph++;
            }
        }
    }

    std::cout << " ------- Results -------- \n";
    std::cout << "Spaces: " << space << "\n";
    std::cout << "Alpha's: " << alpha << "\n";
    std::cout << "Digits: " << digit << "\n";
    std::cout << "Hexadecimal digits: " << xdigit << "\n";
    std::cout << "Uppercase letters: " << uppercase << "\n";
    std::cout << "Lowercase letters: " << lowercase << "\n";
    std::cout << "Alphanumerics: " << alpha << "\n";
    std::cout << "Control characters: " << cntrl << "\n";
    std::cout << "Punctuation marks: " << punct << "\n";
    std::cout << "Printable characters: " << printable << "\n";
    std::cout << "Graphical characters: " << graph << "\n";

    return 0;
}

std::vector<std::string> parseWords(std::ifstream& ist)
{
    std::string line {};
    std::string word {};
    std::vector<std::string> words {};

    if (ist.is_open())
    {
        while (getline(ist, line))
        {
            for (const char& c : line)
            {
                if (isgraph(c))
                {
                    word += c;
                }
                else if (isspace(c))
                {
                    if (!word.empty())
                    {
                        words.push_back(word);
                        word.clear();
                    }
                }
            }
            
            if (!word.empty())
            {
                words.push_back(word);
                words.push_back("\n");
                word.clear();
            }
        }
    }
    else 
    {
        std::cout << "File couldn't open.\n";
    }

    return words;
}