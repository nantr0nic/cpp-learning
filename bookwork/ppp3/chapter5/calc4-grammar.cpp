// Trying to put together all the Bjarne calculator stuff...

#include <iostream>
using namespace std;

// Functions
/*
Token get_token()     // read characters and compose tokens; uses continue;
double expression()    // deal with + and -; calls term() and get_token()
double term()          // deal with *, /, and &; calls primary() and get_token();
double primary()       // deal with numbers and parentheses; calls expression() and get_token();
*/
/*
// This is the 2nd incorrect attempt at expression()
double expression()
{
    double left = term();
    Token t = get_token();
    switch (t.kind) {
    case '+':
        return left + expression();
    case '−':
        return left − expression();
    default:
        return left;
    }
}
    // This works for addition but NOT subtraction because it looks for
    // term then expression, not expression then term
*/

class Token
{
    public:
        char kind;      // what kind of token
        double value;   // for numbers: a value
        Token(char ch)  // make a Token from a char
            :kind(ch), value(0) { }
        Token(char ch, double val)      // make a Token from a char and a double
            :kind(ch), value(val) { }
};

Token get_token()    // read a token from cin
{
    char ch;
    cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

    switch (ch) {
        //not yet   case ';':    // for "print"
        //not yet   case 'q':    // for "quit"
    case '(': case ')': case '+': case '-': case '*': case '/':
        return Token(ch);        // let each character represent itself
    case '.':
    case '0': case '1': case '2': case '3': case '4':
    case '5': case '6': case '7': case '8': case '9':
    {
        cin.putback(ch);         // put digit back into the input stream
        double val;
        cin >> val;              // read a floating-point number
        return Token('8', val);   // let '8' represent "a number"
    }
    default:
        error("Bad token");
    }
}