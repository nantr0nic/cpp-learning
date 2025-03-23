#include <iostream>
#include <stdexcept>
#include <vector>

using std::vector, std::cin, std::cout, std::cerr;

class Token {
    public:
        char kind;
        double value;
        Token(char k) :kind{k}, value{0.0} { }
        Token(char k, double v): kind{k}, value{v} { }
};

Token get_token();
vector<Token> tok;

int main()
{
    // ...
    while (cin)
    {
        Token t = get_token();
        tok.push_back(t);
    }
    // ...
    for (int i = 0;
}