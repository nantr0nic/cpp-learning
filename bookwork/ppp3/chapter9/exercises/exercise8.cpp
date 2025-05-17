/*
Use the program from the previous exercise to make a sorted list of
words. Run the result on a multi-page text file, look at the result, and see
if you can improve the program to make a better list.
*/

#include <iostream>
#include <string>
#include <vector>
#include <cctype>
#include <fstream>

std::vector<std::string> parseWords(const std::string& line);
std::vector<std::string> parseWords(std::ifstream& ist);
std::string tolowerString(std::string& word);
void noContractions(std::vector<std::string>& wordsList);
void noPunctuation(std::vector<std::string>& wordsList);
std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& string);

int main()
{
    std::string fileName {};

    std::cout << "Write a file name \n >> ";
    std::getline(std::cin, fileName);

    std::ifstream ist {fileName};

    if (ist.is_open())
    {
        std::vector<std::string> words {parseWords(ist)};
        std::cout << "Here are the unmodified words!\n";

        for (size_t i {0}; i < words.size(); ++i)
        {
            std::cout << i << ". " << words[i];
            if (words[i] != "\n")
            {
                std::cout << "\n";
            }
        }
        std::cout << words << std::endl;

        std::cout << "Now let's de-contract!\n";
        noContractions(words);
        std::cout << words << std::endl;

        std::cout << "Now let's de-punctuate!\n";
        noPunctuation(words);
        std::cout << words << std::endl;
    }


    return 0;
}

std::vector<std::string> parseWords(const std::string& line)
{
    std::string word {};
    std::vector<std::string> words {};
    for (const char& c : line)
    {
        if (isgraph(c))
        {
            word += c;
        }
        else if (isspace(c) || c == '\n')
        {
            if (!word.empty())
            {
                words.push_back(word);
                word.clear();
            }
        }
    }
    // Add the last word...
    if (!word.empty())
    {
        words.push_back(word);
    }

    return words;
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

std::string tolowerString(std::string& word)
{
    std::string loweredWord {};
    for (char& c : word)
    {
        c = static_cast<char>(tolower(c));
        loweredWord += c;
    }
    return loweredWord;
}

void noContractions(std::vector<std::string>& wordsList)
{

    for (std::string& word : wordsList)
    {
        std::string checkWord {};
        bool contraction {false};
        bool quotes {false};
        bool comma {false};
        bool period {false};

        for (const char& c : word)
        {
            if (c == '"')
            {
                quotes = !quotes;
                break;
            }
        }

        if (quotes)
        {
            continue;
        }

        for (const char& c : word)
        {
            if (isalpha(c) || c == '\'')
            {
                checkWord += c;
            }
            if (c == ',')
            {
                comma = true;
            }
            if (c == '.')
            {
                period = true;
            }
        }
        tolowerString(checkWord);
        if (checkWord == "don't")
        {
            word = "do not";
            contraction = true;
        }
        if (checkWord == "can't")
        {
            word = "cannot";
            contraction = true;
        }
        if (checkWord == "won't")
        {
            word = "will not";
            contraction = true;
        }
        if (checkWord == "let's")
        {
            word = "let us";
            contraction = true;
        }
        if (checkWord == "couldn't")
        {
            word = "could not";
            contraction = true;
        }
        if (checkWord == "shouldn't")
        {
            word = "should not";
            contraction = true;
        }
        if (checkWord == "didn't")
        {
            word = "did not";
            contraction = true;
        }
        if (contraction)
        {
            if (comma)
            {
                word = word + ',';
                comma = false;
            }
            else if (period)
            {
                word = word + '.';
                period = false;
            }
        }
    }
}

void noPunctuation(std::vector<std::string>& wordsList)
{
    bool quotes {false};
    for (std::string& word : wordsList)
    {
        std::string newWord {};
        for (size_t i {0}; i < word.length(); ++i)
        {
            char c = word[i];
            if (c == '"')
            {
                newWord += c;
                quotes = !quotes;
            }
            else if (quotes)
            {
                newWord += c;
            }
            else if (c == '-' && i > 0 && i < word.length() - 1 && 
                    isalpha(word[i-1]) && isalpha(word[i+1]))
            {
                newWord += c;
            }
            else if (ispunct(c))
            {
                newWord += ' ';
            }
            else if (isalnum(c) || isspace(c))
            {
                newWord += c;
            }
        }
        word = newWord;
    }
}

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