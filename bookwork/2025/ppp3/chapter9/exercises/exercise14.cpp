/*
Write a program that reads a file of whitespace-separated numbers and
outputs a file of numbers using scientific format and precision 8 in four
fields of 20 characters per line.
*/

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <format>

int main()
{
    std::string inputFile {"numbers.txt"};
    std::ifstream ist {inputFile};
    if (ist.is_open())
    {
        std::string outputFile {"numbers_output.txt"};
        std::ofstream ost {outputFile};
        if (ost.is_open())
        {
            double number {};
            int entries {1};
            while (ist >> number)
            {
                ost << std::format("{:20.8e}", number);
                entries++;
                if (entries > 4)
                {
                    ost << "\n";
                    entries = 1;
                }
            }

        }
        else
        {
            throw std::runtime_error("Couldn't open file: " + outputFile);
        }
    }
    else
    {
        throw std::runtime_error("Couldn't open file: " + inputFile);
    }

    return 0;
}