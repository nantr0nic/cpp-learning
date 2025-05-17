/*
Reverse the order of words (defined as whitespace-separated strings) in a
file. For example, Norwegian Blue parrot becomes parrot Blue Norwegian.
Assume that all the strings from the file will fit into memory at once.
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>

std::vector<std::string> parseWords(std::ifstream& ist);
std::vector<std::string> reverseWords(std::vector<std::string>& wordsVector);
std::vector<std::string> doubleReverseWords(std::vector<std::string>& wordsVector);
std::string reverseLetters(std::string& string);

std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& wordsList)
{
    for (const std::string& word : wordsList)
    {
        os << word;
        if (word != "\n")
        {
            os << " ";
        }
    }
    return os;
}

int main()
{
    std::string fileName {};
    std::cout << "Enter the name of a file: ";
    std::cin >> fileName;
    std::ifstream ist {fileName};
    std::vector<std::string> words {parseWords(ist)};
    std::cout << words;

    std::cout << "I'm going to print the words of that file in reverse:\n\n";
    std::vector<std::string> revWords {reverseWords(words)};
    std::cout << revWords;

    std::cout << "\nNow I'm going to reverse the words again...\n";
    std::vector<std::string> revWords2 {doubleReverseWords(words)};
    std::cout << revWords2;

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

std::vector<std::string> reverseWords(std::vector<std::string>& wordsVector)
{
    std::vector<std::string> reverseWords {};

    if (wordsVector.size() > 0)
    {
        for (int i = static_cast<int>(wordsVector.size()) - 1; i >= 0; --i)
        {
            reverseWords.push_back(wordsVector[i]);
        }
    }

    return reverseWords;
}

std::vector<std::string> doubleReverseWords(std::vector<std::string>& wordsVector)
{
    std::vector<std::string> reverseWords {};

    if (wordsVector.size() > 0)
    {
        for (int i = static_cast<int>(wordsVector.size()) - 1; i >= 0; --i)
        {
            std::string reversedWord = reverseLetters(wordsVector[i]);
            reverseWords.push_back(reversedWord);
        }
    }

    return reverseWords;
}
std::string reverseLetters(std::string& string)
{
    std::string reversed {};
    for (int i = string.length(); i >= 0; --i)
    {
        reversed += string[i];
    }

    return reversed;
}