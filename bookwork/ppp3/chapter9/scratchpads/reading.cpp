#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct Reading {        // a temperature reading
    int hour;           // hour after midnight [0:23]
    double temperature; // in Fahrenheit
};

std::ostream& operator<<(std::ostream& os, const Reading& r)
{
    return os << "{hour:" << r.hour << ", temperature:" << r.temperature << "}\n";
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
    os << "[";
    if (!vec.empty())
    {
        os << vec[0];
        for (size_t i = 1; i < vec.size(); ++i)
        {
            os << ", " << vec[i];
        }
    }
    os << "]";
    return os;
}

int main()
{
    std::vector<Reading> temps;  // store the readings here
    int hour {};
    double temperature {};
    std::string ifilename = "tempdata.txt";
    std::ifstream ist {ifilename};
    while (ist >> hour >> temperature)
    {
        if (hour < 0 || 23 < hour)
            throw std::runtime_error("Hour out of range");
        temps.push_back(Reading{hour,temperature});
    }
    std::cout << temps;

    std::string ofilename = "tempdataoutput.txt";
    std::ofstream ost {ofilename};
    for (Reading x : temps)
    {
        ost << '(' << x.hour << ',' << x.temperature << ")\n";
    }

    return 0;
}