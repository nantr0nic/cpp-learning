#include <iostream>

using std::cin, std::cout;

int main()
{
    int comp_guess = 50;
    char prompt = 'y';

    cout << "Think of a number between 1 and 100 and I'll try to guess it!\n"
    cout << "Is the number less than " << comp_guess << "?\n";
    cout << "(y/n) >> ";
    cin >> prompt;
    if (prompt == 'y')
    {
        comp_guess -= 25;
        cout << "Is the number less than " << comp_guess << "?\n";
