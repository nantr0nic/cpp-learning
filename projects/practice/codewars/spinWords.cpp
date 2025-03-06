/*
Write a function that takes in a string of one or more words, and
returns the same string, but with all words that have five or more letters reversed.
Strings passed in will consist of only letters and spaces.
Spaces will be included only when more than one word is present.
*/

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

string spinWords(const string &str)
{
    istringstream iss(str);
    string token = "";
    vector<string> tokens;

    while (iss >> token)
    {
        if (token.length() >= 5)
        {
            reverse(token.begin(), token.end());
        }
        tokens.push_back(token);
    }

    string result = "";
    for (const auto& t : tokens)
    {
        if (!result.empty()) result += " ";
        result += t;
    }

    return result;
}

int main()
{
    string phrase = "";
    cout << "Enter a string\n >> ";
    getline(cin, phrase);
    // cin >> phrase; <-- only captures until the whitespace
    cout << spinWords(phrase);
}

/*
#include <string>
#include <algorithm>
#include <sstream>
std::string spinWords(const std::string &str)
{
    std::stringstream ss(str);
    std::string result;
    std::string buff;
    while (ss >> buff) {
        if (buff.size() >= 5) {
            std::reverse(buff.begin(), buff.end());
        }
        result += buff + ' ';
    }
    result.pop_back();
    return result;
}
*/