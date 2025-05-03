/*
This exercise is to read a poorly formatted file of sensor readings. From the book:

Let’s try to use this “standard loop” for a concrete example. As usual, we’ll
use the example to illustrate widely applicable design and programming
techniques. Assume that you have a file of temperature readings that has been
structured like this:
- A file holds years (of months of readings). A year starts with { year
    followed by an integer giving the year, such as 1900, and ends with }.
- A year holds months (of days of readings). A month starts with { month
    followed by a three-letter month name, such as jan, and ends with }.
- A reading holds a time and a temperature. A reading starts with a (
    followed by day of the month, hour of the day, and temperature and ends
    with a ).
*/

// In its current state, this file is for study and not (yet) meant to be compilable.

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using std::cout, std::cin, std::string, std::vector, std::istream;

// Global variables = bad but this is for the sake of the exercise.
const int not_a_reading = -7777;
const int not_a_month = -1;
// min/max for temperature readings
constexpr int implausible_min = -200;
constexpr int implausible_max = 200;
// month tables
vector<string> month_input_tbl = { "-not a month-",
    "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"
};
vector<string> month_print_tbl = { "-not a month-",
    "January", "February", "March", "April", "May", "June", "July", "August",
    "September", "October", "November", "December"
};

int month_to_int(string s)
    // is s the name of a month? if so return tis index [1:12] otherwise -1
{
    for (int i = 1; i < 13; ++i)
    {
        if (month_input_tbl[i] == s)
        {
            return i;
        }
    }
    return 0;
}

string int_to_month(int m)
{
    if (m < 1 || 12 < m)
    {
        throw std::runtime_error("bad month index");
    }
    return month_print_tbl[m];
}

void end_of_loop(istream& ist, char term, const string& message)
{
    if (ist.fail())     // use term as terminator and/or separator
    {
        ist.clear();
        char ch = 0;
        if (ist >> ch && ch == term)
        {
            return;     // all is fine
        }
        throw std::runtime_error(message);
    }
}

struct Day {
    vector<double> temp = vector<double>(24,not_a_reading);
};

struct Month {
    int month = not_a_month;           // [0:11] Jan is 0  
    vector<Day> day = vector<Day>(32); // [1:31] one vector of readings
    // '32' because we waste '0' for simplicity
};

struct Year {
    int year {};
    vector<Month> month = vector<Month>(12);
};

struct Reading {
    int day {};
    int hour {};
    double temperature {};
};

istream& operator>>(istream& is, Reading& r)
    // read a temperatur reading from is into r. format:( 3 4 9. 7)
    // check format, but don't bother with data validity
{
    char ch1;
    if (is >> ch1 && ch1 != '(')
    {
        is.unget();
        is.clear(std::ios::failbit);
        return is;
    }

    char ch2;
    if ((is >> r.day >> r.hour >> r.temperature >> ch2) && ch2 != ')')
    {
        throw std::runtime_error("Bad reading");
    }
    return is;
}

bool is_valid(const Reading& r)
    // a rough test
{
    if (r.day < 1 || 31 < r.day)
    {
        return false;
    }
    if (r.hour < 0 || 23 < r.hour)
    {
        return false;
    }
    if (r.temperature < implausible_min || implausible_max < r.temperature)
    {
        return false;
    }

    return true;
}

istream& operator>>(istream& is, Month& m)
    // read a month from is into m. format: {month feb ... }
{
    char ch = 0;
    if (is >> ch && ch != '{')
    {
        is.unget();
        is.clear(std::ios::failbit);    // we failed to read a Month
        return is;
    }

    string month_marker;
    string mm;
    is >> month_marker >> mm;
    if (!is || month_marker != "month")
    {
        throw std::runtime_error("bad start of the month");
    }
    m.month = month_to_int(mm);

    int duplicates = 0;
    int invalids = 0;
    for (Reading r; is >> r; )
    {
        if (is_valid(r))
        {
            // I think the book's "m.day[r.day].hour[r.hour]" is wrong.
            // I think the following line is correct.
            if (m.day[r.day].temp[r.hour] != not_a_reading)
            {
                ++duplicates;
            }
            m.day[r.day].temp[r.hour] = r.temperature;
        }
        else
        {
            ++invalids;
        }
    }
    if (invalids)
    {
        throw std::runtime_error("invalid readings in month " + invalids);
    }
    if (duplicates)
    {
        throw std::runtime_error("duplicate readings in month " + duplicates);
    }
    end_of_loop(is,'}',"bad end of month");
    return is;
}

istream& operator>>(istream& is, Year& y)
    // read a year from is into y. format: { year 1972 ... }
{
    char ch = 0;
    is >> ch;
    if (ch != '{')
    {
        is.unget();
        is.clear(std::ios::failbit);
        return is;
    }

    string year_marker;
    int yy = -1;
    is >> year_marker >> yy;
    if (!is || year_marker != "year")
    {
        throw std::runtime_error("bad start of year");
    }
    y.year = yy;

    while (true)
    {
        Month m;        // get a clean m each time around
        if (!(is >> m))
        {
            break;
        }
        y.month[m.month] = m;
    }

    end_of_loop(is,'}',"bad end of year");

    return is;
}

int main()
{
    // open an input file:
    cout << "Please enter input file name\n >> ";
    string iname;
    cin >> iname;
    std::ifstream ifs {iname};
    if (!ifs)
    {
        throw std::runtime_error("can't open input file " + iname);
    }
    ifs.exceptions(ifs.exceptions() | std::ios::badbit);    // throw for bad()

    // open an output file:
    cout << "Please enter output file name\n >> ";
    string oname;
    cin >> oname;
    std::ofstream ofs {oname};
    if (!ofs)
    {
        throw std::runtime_error("can't open output file " + oname);
    }
    
    // read an arbitrary number of years:
    vector<Year> ys;
    while(true)
    {
        Year y;
        if(!(ifs >> y))
        {
            break;
        }
        ys.push_back(y);
    }

    cout << "read " << ys.size() << " years of readings\n";

    for (const Year& y : ys)
    {
        print_year(ofs, y);     // leaving print_year() for an exercise.
    }

    return 0;
}