/*
Write a program that produces the sum of all the numbers in a file of
whitespace-separated integers.
*/

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

double sumNumFile (const std::string& filename)
{
    std::ifstream ist {filename};
    if (!ist.is_open())
    {
        throw std::runtime_error("Couldn't open file: " + filename);
    }
    
    double sum {};
    double number {};
    while (ist >> number)
    {
        sum += number;
    }

    if (ist.bad())
    {
        throw std::runtime_error("Error reading file: " + filename);
    }

    return sum;
}

int main()
{
    try
    {
        std::string filename {"numbers.txt"};
        double sum {sumNumFile(filename)};
        std::cout << "The sum of the numbers in " << filename << " is: " << sum << std::endl;
        return 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
}