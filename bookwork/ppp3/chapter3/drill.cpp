/*
1. Program prompts the user for a length (value + unit) in cm, m, in, or ft.
2. Program checks if unit is legal, if it is, then
3. Converts value to CM (if needed) and then
4. Keeps track of smallest and largest values entered, amount of entries made,
    their total sum, and lists the entries made while the program is running.
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::cout, std::cin, std::string, std::vector;

//////// Function Declarations ////////////
// convert everything to cm cuz Bjarne is crazy
double convToCm(double x, const string& unit);
// function to check unit legality
bool isValidUnit(const string& unit, const vector<string>& legalUnits);
// print results function
void printResults(
    double smallest, double largest, unsigned short entries, double sum,
    vector<double>& inputValues);

////////// Main //////////
int main()
{
    double value{0}, converted{0}, smallest{0}, largest{0}, sum{0};
    string unit = "";
    const vector<string> legal = {"cm", "m", "in", "ft"};
    vector<double> inputValues;
    unsigned short entries = 0;
    bool running = true;

    // main loop - using 'running' so could be set to false if needed in the future
    while(running)
    {
        // get inputs: value (double) and unit (string)
        cout << "Enter value and unit (e.g. 6ft, 100m, 2.78in, 9cm)\n >> ";
        cin >> value >> unit;

        // check if unit is illegal
        if (!isValidUnit(unit, legal))
        {
            cout << "You entered an invalid unit!\n";
            cout << "Please use: cm, m, ft, in.\n";
            continue;
        }

        // if it is legal then convert it to cm and carry on
        converted = convToCm(value, unit);
        cout << "You entered " << value << unit << " which is " << converted << "cm!\n";
        // value gets the new converted value
        value = converted;

        // if this is the first entry, set smallest/largest to the first input value
        if (entries == 0)
        {
            smallest = largest = value;
        }

        ++entries;      // increment entries cuz keeping track of total entries
        sum += value;       // add the input cm to total sum of inputs cuz keeping track
        inputValues.push_back(value); // add the input to list of entered inputs cuz... etc.

        // do the comparison and adjust recorded largest/smallest as needed
        if (value > largest)
            largest = value;
        if (value < smallest)
            smallest = value;

        // print the tracked shit
        printResults(smallest, largest, entries, sum, inputValues);
    }

    return 0;
}

// I know these are "magic constants" but these should be mostly familiar
// so I'll save the space and keep these
double convToCm(double x, const string& unit)
{
    double j = 0;
    if (unit == "m")
        j = x * 100;
    if (unit == "cm")
        j = x;
    if (unit == "in")
        j = x * 2.54;
    if (unit == "ft")
        j = x * 30.48;
    return j;
}

void printResults(
    double smallest, double largest, unsigned short entries, double sum, 
    vector<double>& inputValues)
    {
        // print the tracked shit
        cout << "------------------------------\n";
        cout << "smallest so far: " << smallest << "cm\n";
        cout << "largest so far: " << largest << "cm\n";

        // print number of entries and sum of entries
        cout << "number of entries: " << entries << "\n";
        cout << "sum of entries: " << sum << "cm\n";

        // sort and print previous entries...
        // we'll keep Bjarne happy and use meters in addition to cm
        std::sort(inputValues.begin(), inputValues.end());
        cout << "--- Previous entries ---\n";
        for (double z : inputValues)
            cout << z << "cm // " << z / 100 << "m\n";
        cout << "------------------------------\n\n";
    }

bool isValidUnit(const string& unit, const vector<string>& legalUnits)
{
    for (const auto& legalUnit : legalUnits)
    {
        if (unit == legalUnit)
            return true;
    }
    return false;
}