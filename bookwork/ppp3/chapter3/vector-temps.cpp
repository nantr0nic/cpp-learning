#include <iostream>
#include <vector>
#include <algorithm>

using std::cout, std::cin, std::vector;

int main()
{
    vector<double> temps;           // temperatures
    for (double temp; cin>>temp;)    // read into temp
    {
        temps.push_back(temp);      // put temp into vector
    }

    // compute mean temperature:
    double sum = 0;
    for (double x : temps)
    {
        sum += x;
    }
    cout << "Average temperature: " << sum / temps.size() << '\n';

    // compute median temperature:
    std::sort(temps.begin(), temps.end());
    cout << "Median temperature: " << temps[temps.size()/2] << '\n';

    return 0;
}