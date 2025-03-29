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

Token get_token();                  // function to read a token from cin
vector<Token> tok;                  // we'll put the tokens here

int main()
{
    // ...
    while (cin)
    {
        Token t = get_token();
        tok.push_back(t);
    }
    // ...
    for (int i = 0; i < tok.size(); ++i)        // loop through tokens
    {
        if (tok[i].kind == '*')                 // found a multiply!
        {
            // d = value of token before i * value of token after i
            double d = tok[i-1].value*tok[i+1].value;
            cout << d;
            // now what?
        }
    }
}