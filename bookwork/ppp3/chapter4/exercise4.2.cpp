/*
This is the code provided in the book. Fix it.

double ctok(double c)       // converts C to Kelvin
{
    int k = c + 273.25;
    return int;
}

int main()
{
    double c = 0;           // declare input variable
    cin >> d;               // retrieve temperature to input variable
    double k = ctok("c");   // convert temperature

    Cout << k << '\n';
    return 0;
}
*/

#include <iostream>

double ctok(double c)       // converts Celsius to Kelvin
{
    double minimum_temp = -273.15;
    if (c < minimum_temp)
    {
        std::cerr << "Below absolute zero! Choose a warmer temperature.\n";
        return 0;
    }
    double k = c + 273.15;
    return k;
}

int main()
{
    double c = 0;           // declare input variable
    std::cin >> c;
    double k = ctok(c);     // convert temperature

    std::cout << k << '\n';
    return 0;
}