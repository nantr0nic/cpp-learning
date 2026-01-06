/*
Write a program that accepts two file names and produces a new file that
is the contents of the first file followed by the contents of the second;
that is, the program concatenates the two files.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <stdexcept>

int main()
{
    std::string ifname1 {};
    std::string ifname2 {};

    // Get the first file
    std::cout << "Please enter the name of file 1: ";
    std::cin >> ifname1;
    std::ifstream ist1 {ifname1};
    if (!ist1.is_open())
    {
        throw std::runtime_error("Couldn't open file: " + ifname1);
    }

    // Get the second file
    std::cout << "Please enter the name of file 2: ";
    std::cin >> ifname2;
    std::ifstream ist2 {ifname2};
    if (!ist2.is_open())
    {
        throw std::runtime_error("Couldn't open file: " + ifname2);
    }

    // Open the output file
    std::string ofname {"concatenated.txt"};
    std::ofstream ost {ofname};
    if (!ost.is_open())
    {
        throw std::runtime_error("Couldn't open file: " + ofname);
    }

    // Write the contents of the first file to output file
    std::string line {};
    while (std::getline(ist1, line))
    {
        ost << line << '\n';
    }

    ist1.close();

    // Write the contents of the second file to output file
    while (std::getline(ist2, line))
    {
        ost << line << '\n';
    }

    ist2.close();

    std::cout << "The two files have been combined into \"" << ofname << "\" -- hopefully!" << std::endl;

    ost.close();

    return 0;
}