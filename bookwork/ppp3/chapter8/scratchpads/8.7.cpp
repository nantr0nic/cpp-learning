// Currently doesn't compile. Working through the examples that are building up to
// a robust example of struct, enum, and class.

#include <iostream>
#include <stdexcept>
#include <exception>
#include <vector>

struct Year {
    int y;
};

enum class Month {
    jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

// Monday = 0, Tuesday = 1 and so on to Sunday = 6
enum class Day {
    monday, tuesday, wednesday, thursday, friday, saturday, sunday
};

// Bad practice! Boo global variables! But for educational reasons...
std::vector<std::string> month_table = {
    "Not a month",
    "January",
    "February",
    "March",
    "April",
    "May",
    "June",
    "July",
    "August",
    "September",
    "October",
    "November",
    "December"
};

// Converts month to int type
int to_int(Month m)
{
    return static_cast<int>(m);
}

// Makes a Month object out of an int
Month int_to_month(int x)
{
    if (x<to_int(Month::jan) || to_int(Month::dec)<x)
    {
        throw std::runtime_error("Invalid month!");
    }
    return Month{x};
}

// Overload ++ to increment months and wrap aroung
Month operator++(Month& m)
{
    m = (m == Month::dec) ? Month::jan : Month{to_int(m)+1};    // arithmetic if to wrap around
    return m;
}

// Overload << to output month names
std::ostream& operator<<(std::ostream& os, Month m)
{
    return os << month_table[to_int(m)];
}

// Date class
class Date {
    public:
        class Invalid { };              // to be used as exception
        Date(Year y, Month m, int d);      // constructor: check for valid date and initialize
        bool is_valid();                // return true if date is valid
        // void add_day(int n);            // increase the Date by n days
        // void add_mon(int n);            // increase the Date by n months
        int year() { return y; }
        int month() { return to_int(m); }
        int day() { return d; }

    private:
        Year y;      // year
        Month m;    // month
        int d;      // day
};

Date::Date(Year y, Month m, int dd)      // constructor
    : y{y}, m{m}, d{dd}               // member initliazation list
{ 
    if (!is_valid())
    {
        throw Invalid{};
    }
}

bool Date::is_valid()
{
    return 0<to_int(m) && to_int(m)<13;
}
/*
void Date::add_mon(int n)
{
    try {
        m += n;
        if (!is_valid())
        {
            throw Invalid();
        }
    }
    catch(Date::Invalid) {
        std::cout << "Invalid month!\n";
        throw Invalid();    // this will be caught by catch in main(), printing 'Bad date!'
    }
}
*/

std::ostream& operator<<(std::ostream& os, Date d)
{
    return os << d.year() << "/" << d.month() << "/" << d.day();
}

int main()
{
    try {
        int month_num = 0;
        std::cout << "Enter a number for a month\n >> ";
        std::cin >> month_num;
        Month mm = int_to_month(month_num);
        std::cout << "The month you entered was " << mm;

        std::cout << "\nLet's increment the month three times.\n";
        ++mm;
        std::cout << "The month is now " << mm;
        ++mm;
        std::cout << "\nThe month is now " << mm;
        ++mm;
        std::cout << "\nThe month is now " << mm;

        Date dx1 {Year{2025}, Month::apr, 14};
        std::cout << "\n" << dx1 << "\n";

        Date dx2 {Year{1991}, int_to_month(2), 6};
        std::cout << "\n" << dx2 << "\n";
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << "Runtime error: " << e.what() << "\n";
        return 1;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Unexpected error: " << e.what() << "\n";
        return 2;
    }
    catch (...)
    {
        std::cerr << "Unknown exception.\n";
        return 2;
    }

    return 0;
}
