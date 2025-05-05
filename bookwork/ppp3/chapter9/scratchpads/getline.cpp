#include <iostream>
#include <string>

void lowerize(std::string& s)
{
    for (char& x : s)
    {
        x = tolower(x);
    }
}

std::string get_sentence()
{
    std::cout << "Now, enter a sentence or whatever you want.\n >> ";
    std::string sentence;

    char c {};

    while ((c = std::cin.get()) != '\n')
    {
        sentence += c;
    }

    return sentence;
}

int main()
{
    std::cout << "Enter your full name: ";
    std::string getline_name;
    getline(std::cin, getline_name);
    std::cout << getline_name << "\n";

    // Bjarne evidently doesn't like getline()... so...
    std::string sentence = get_sentence();
    std::cout << sentence << "\n";
    // Let's try...
    lowerize(sentence);
    std::cout << sentence;


    return 0;
}