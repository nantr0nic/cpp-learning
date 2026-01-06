// Implementing tokens
#include <iostream>
#include <stdexcept>

class Token {
    public:
        char kind;
        double value;
        //Token(char k) :kind{k}, value{0.0} { }
        //Token(char k, double v): kind{k}, value{v} { }
};

int main()
{
    try
    {
        Token t;
        t.kind = '+';
        Token t2;
        t2.kind = '8';
        t2.value = 3.14;
        Token tt = t;
        if (tt.kind != t.kind)
            throw std::runtime_error("Impossible!");
        t = t2;
        std::cout << t.value;
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown error." << std::endl;
        return 2;
    }
}
