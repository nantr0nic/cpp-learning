/*
Modify the program from the previous exercise so that it replaces don’t
with do not, can’t with cannot, etc.; leaves hyphens within words intact
(so that we get “do not use the as−if rule ”); and converts all characters to
lowercase.
*/

#include <iostream>
#include <string>
#include <vector>
#include <cctype>

std::vector<std::string> parseWords(const std::string& line);
std::vector<std::string> parseWords(const std::ifstream& ist);
std::string tolowerString(std::string& word);
void noContractions(std::vector<std::string>& wordsList);
void noPunctuation(std::vector<std::string>& wordsList);
std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& string);

int main()
{
    std::string line {};

    std::cout << "Write a line you want changed\n >> ";
    std::getline(std::cin, line);

    std::vector<std::string> words {parseWords(line)};
    std::cout << words << "\n";

    std::cout << "\nLet's change contractions now\n";
    noContractions(words);
    std::cout << words;

    std::cout << "\nLet's disempunctuate those words now...\n";
    noPunctuation(words);
    std::cout << words;


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
        else if (isspace(c))
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

std::string tolowerString(std::string& word)
{
    std::string loweredWord {word};
    for (char& c : word)
    {
        c = static_cast<char>(tolower(c));
    }
    return loweredWord;
}

void noContractions(std::vector<std::string>& wordsList)
{
    bool comma {false};
    bool period {false};

    for (std::string& word : wordsList)
    {
        std::string checkWord {};
        bool contraction {false};

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
        if (contraction)
        {
            if (comma)
            {
                word = word + ',';
                comma = !comma;
            }
            else if (period)
            {
                word = word + '.';
                period = !period;
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
        os << word << " ";
    }
    return os;
}