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
        // Various default constructors:
        Date() { };              // using default values of members in private
        Date(Year y);       // Jan 1 of year y      // must define below class block
        Date(Year y, Month m, int d);      // constructor: check for valid date and initialize
        bool is_valid();                // return true if date is valid
        // void add_day(int n);            // increase the Date by n days
        // void add_mon(int n);            // increase the Date by n months
        int year() const { return y.y; }
        int month() const { return to_int(m); }
        int day() const { return d; }

    private:
        Year y { 2001};         // THESE are default member initializers...
        Month m = Month::jan;
        int d = 1;
};
/*
Date::Date()
    : y{Year{2001}}, m{Month::jan}, d{1}
    { }
*/
Date::Date(Year yy)     // specified initializers for m and d are 
    : y{yy}
    { }

Date::Date(Year y, Month m, int dd)      // constructor
    : y{y}, m{m}, d{dd}                  // member initialization list
{ 
    if (!is_valid())
    {
        throw Invalid{};
    }
}
/*
Default constructor that takes no arguments:
Date::Date()
    : y{Year{2001}}, m{Month::jan}, d{1}
    { }
*/

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
        int month_num = 10;
        Month mm = int_to_month(month_num);
        std::cout << "The 10th month is " << mm;

        std::cout << "\nLet's increment the month three times.\n";
        for (int i = 0; i < 3; ++i)
        {
            ++mm;
            std::cout << "The month is now " << mm << "\n";
        }
        
        Date dx1 {Year{2025}, Month::apr, 14};
        std::cout << "\n" << dx1 << "\n";

        Date dx2 {Year{1991}, int_to_month(2), 6};
        std::cout << "\n" << dx2 << "\n\n";

        // Copying
        Date holiday {Year{1978}, Month::jul, 4};       // initialization
        Date d2 = holiday;
        std::cout << "holiday = " << holiday << "\n";
        std::cout << "d2 = " << d2 << "\n";
        Date d3 = {Year{1978}, Month::jul, 4};
        std::cout << "d3 = " << d3 << "\n";
        holiday = Date{Year{1978}, Month::dec, 24};     // assignment
        std::cout << "holiday = " << holiday << "\n";
        d3 = holiday;
        std::cout << "d3 = " << d3 << "\n";

        Date d4 {d3};       // uses copy constructor
        std::cout << "d4 = " << d4 << "\n\n";

        // unnamed object
        std::cout << Date{Year{1999}, Month::dec, 31} << "\n";

        // another unnamed object using the default constructor with no arguments
        std::cout << Date{} << "\n\n";

        // Some default initializations with built-in types
        std::cout << int{} << "\n";     // should print just a '0'
        int y {};
        std::cout << "int y {} = " << y << "\n";
        std::cout << "And +1 is..." << ++y << "\n";
        double y2 {};
        std::cout << "double y2 {} = " << y2 << "\n";
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
