/*
[7] Read five names into a vector<string> name, then prompt the user for the
ages of the people named and store the ages in a vector<double> age.
Then print out the five (name[i],age[i]) pairs. Sort the names
(sort(name.begin(),name.end())) and print out the (name[i],age[i]) pairs. The
tricky part here is to get the age vector in the correct order to match the
sorted name vector. Hint: Before sorting name, take a copy and use that to
make a copy of age in the right order after sorting name.
[8] Do the previous exercise but allow an arbitrary number of names.
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using std::cin, std::cout, std::vector, std::string;

// Functions //
void name_sort(vector<string>& names, vector<double>& ages);
// Not using templates yet so DOUBLE OVERLOAD!
std::ostream& operator<<(std::ostream& os, const vector<string>& vec);
std::ostream& operator<<(std::ostream& os, const vector<double>& vec);

int main()
{
    vector<string> names = {"Andy", "Heather", "AP", "Jill", "Luz"};
    vector<double> ages;
    double age = 0;
    for (auto name : names)
    {
        cout << "How old is " << name << "?\n >> ";
        cin >> age;
        ages.push_back(age);
    }
    cout << "\nFantastic! Here's the first result.\n";
    for (unsigned long int i = 0; i < names.size(); ++i)
    {
        cout << "(" << names[i] << ", " << ages[i] << ")\n";
    }

    cout << "Alrighty... now for the forlorn sorting function...\n";
    name_sort(names, ages);
    cout << "Did it work?\n";
    for (unsigned long int i = 0; i < names.size(); ++i)
    {
        cout << "(" << names[i] << ", " << ages[i] << ")\n";
    }
    return 0;
}

void name_sort(vector<string>& names, vector<double>& ages)
{
    vector<string> names_presort = names;
    vector<double> sorted_ages;
    std::sort(names.begin(), names.end());

    for (unsigned long int i = 0; i < names.size(); ++i)
    {
        for (unsigned long int j = 0; j < names_presort.size(); ++j)
        {
            if (names_presort[j] == names[i])
            {
                sorted_ages.push_back(ages[j]);
                break;
            }
        }
    }
    ages = sorted_ages;
}

// Overload << for vector<string>
std::ostream& operator<<(std::ostream& os, const vector<string>& vec)
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

// Overload for vector<double>
std::ostream& operator<<(std::ostream& os, const vector<double>& vec)
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