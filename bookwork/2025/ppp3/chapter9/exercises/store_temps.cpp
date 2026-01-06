#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <stdexcept>

struct Reading
{
    int hour;
    double temp;
};

int main()
{
    std::vector<Reading> temps;
    std::cout << "Let's enter some data temperatures!\n";
    std::cout << "We'll enter the hour and the temperature.\n";
    std::cout << "(enter a non-numeric value to stop)\n";

    int inputHour {};
    double inputTemp {};

    // Let's assume these temp limits (in F)
    constexpr double tempLowLimit = -100;
    constexpr double tempHighLimit = 150;

    while (true)
    {
        // Enter hour first
        std::cout << "Hour (0-23): ";
        if (!(std::cin >> inputHour))
        {
            // Input failed, break
            break;
        }
        if (inputHour < 0 || inputHour > 23)
        {
            std::cout << "Please enter hour within range 0 - 23.\n";
            continue;
        }

        // Enter temperature
        std::cout << "Temperature: ";
        if (!(std::cin >> inputTemp))
        {
            // Input failed, break
            break;
        }
        if (inputTemp < tempLowLimit || inputTemp > tempHighLimit)
        {
            std::cout << "Temperature is outside accepted range (-100 - 150).\n";
            std::cout << "Please re-enter your inputs!\n";
            continue;
        }

        // If success, add to vector
        temps.push_back(Reading{ inputHour, inputTemp });

        // Print confirmation message
        std::cout << "Added reading \""<< inputHour << " " << inputTemp << "\"" << std::endl;

    }

    // Now that we have our vector, write it to file.
    std::string outputFile {"raw_temps.txt"};
    std::ofstream ost {outputFile};
    if (!ost.is_open())
    {
        throw std::runtime_error("Couldn't open the file: " + outputFile);
    }

    for (const Reading& r : temps)
    {
        ost << r.hour << " " << r.temp << "\n";
    }

    std::cout << "Succesfully wrote " << temps.size() << " readings to " << outputFile << "!" << std::endl;

    return 0;
}