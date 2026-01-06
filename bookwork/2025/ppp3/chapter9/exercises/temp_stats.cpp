#include <iostream>
#include <fstream>
#include <stdexcept>
#include <vector>
#include <string>
#include <algorithm>

void sortVector(std::vector<double>& vec)
{
    for (size_t i {0}; i < vec.size() - 1; ++i)
    {
        for (size_t j {0}; j < vec.size() - i - 1; ++j)
        {
            if (vec[j] > vec[j + 1])
            {
                double temp {vec[j]};
                vec[j] = vec[j + 1];
                vec[j + 1] = temp;
            }
        }
    }
}

int main()
{
    std::string inputFile {"raw_temps.txt"};
    std::ifstream ist {inputFile};
    if (!ist.is_open())
    {
        throw std::runtime_error("Couldn't open file: " + inputFile);
    }

    int hour {};
    double temp {};
    std::vector<double> temps {};

    while (ist >> hour >> temp)
    {
        temps.push_back(temp);
    }

    double sum {};
    for (const double& n : temps)
    {
        sum += n;
    }
    std::cout << "The sum of the temps is " << sum << "\n";

    double mean {sum / static_cast<double>(temps.size())};
    std::cout << "The mean of the temps is " << mean << "\n";

    std::cout << "Sorting the temps by least to greatest\n";
    // std::sort(temps.begin(), temps.end());
    
    // Bjarne hasn't introduced std::sort yet (I think), so I wrote a vector sorting function.
    // Note that it will be slower than std::sort...
    sortVector(temps);

    double median {};
    // If even number of readings, median will be the average between the two middle numbers
    if (temps.size() % 2 == 0)
    {
        size_t index1 = (temps.size() / 2) - 1;
        size_t index2 = (temps.size() / 2);
        median = (temps[index1] + temps[index2]) / 2.0;
    }
    // If odd number of readings, median will simply be the middle number
    else
    {
        median = temps[temps.size() / 2];
    }
    std::cout << "The median temperature is " << median << "\n";

    return 0;
}