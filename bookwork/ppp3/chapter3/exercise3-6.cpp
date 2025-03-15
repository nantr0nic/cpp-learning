#include <iostream>

using std::cin, std::cout;

int main()
{
    double value1{0}, value2{0};
    char op = 'x';
    bool running = true;

    while (running)
    {
        cout << "Please enter two values followed by an operator (e.g. +, -, *, or /)\n";
        cout << "(To exit, use operator '?' with any two values.)\n >> ";
        cin >> value1 >> value2 >> op;
        switch (op)
        {
            case '+':
                cout << "The sum of " << value1 << " and " << value2 << " is " << value1 + value2 << "\n\n";
                break;
            case '-':
                cout << "The difference of " << value1 << " and " << value2 << " is " << value1 - value2 << "\n\n";
                break;
            case '*':
                cout << "The product of " << value1 << " and " << value2 << " is " << value1 * value2 << "\n\n";
                break;
            case '/':
                cout << "The quotient of " << value1 << " and " << value2 << " is " << value1 / value2 << "\n\n";
                break;
            case '?':
                cout << "Farewell!\n\n";
                running = false;
                break;
            default:
                cout << "Invalid entry!\n";
                break;
        }
    }
    return 0;
}