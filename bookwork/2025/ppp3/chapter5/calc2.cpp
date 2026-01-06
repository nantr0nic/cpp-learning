#include <iostream>
#include <stdexcept>


using std::cout, std::cin, std::cerr;

int main()
{
    try
    {
        cout << "Please enter expression (we can handle +, -, *, and /)\n";
        cout << "add an x to end expression (e.g., 1+2*3x): ";
        int lval = 0;
        int rval = 0;
        cin >> lval;
        if (!cin)
        {
            throw std::runtime_error("No first operand");
        }

        for (char op; cin>>op;)
        {
            if (op != 'x')
            {
                cin >> rval;
            }
            if (!cin)
            {
                throw std::runtime_error("No second operand");
            }
            switch (op)
            {
                case '+':
                    lval += rval;
                    break;
                case '-':
                    lval -= rval;
                    break;
                case '*':
                    lval *= rval;
                    break;
                case '/':
                    lval /= rval;
                    break;
                default:
                    cout << "Result: " << lval << '\n';
                    return 0;
            }
        }
        throw std::runtime_error("Bad expression");
    }
    catch (const std::runtime_error& e)
    {
        cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    catch (const std::exception& e)
    {
        cerr << "Unexpected error: " << e.what() << std::endl;
        return 2;
    }
    catch (...)
    {
        cout << "Unknown error" << std::endl;
        return 2;
    }
}