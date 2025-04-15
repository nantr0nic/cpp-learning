#include <iostream>

class Date {
    public:
        class Invalid { };              // to be used as exception
        Date(int y, int m, int d);      // constructor: check for valid date and initialize
        bool is_valid();                // return true if date is valid
        // void add_day(int n);            // increase the Date by n days
        void add_mon(int n);            // increase the Date by n months
        int year() { return y; }
        int month() { return m; }
        int day() { return d; }

    private:
        int y, m, d;                // year, month day
};

Date::Date(int yy, int mm, int dd)      // constructor
    : y{yy}, m{mm}, d{dd}               // member initliazation list
{ 
    if (!is_valid())
    {
        throw Invalid{};
    }
}

bool Date::is_valid()
{
    return 0<m && m<13;
}

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


std::ostream& operator<<(std::ostream& os, Date d)
{
    return os << d.year() << "/" << d.month() << "/" << d.day();
}

int main()
{
    Date today {2025, 4, 14};
    std::cout << today << "\n";

    // today.add_day(5);
    // std::cout << today << "\n";

    try {
        Date whoops {2024, 12, 29};
        std::cout << whoops << "\n";
        std::cout << "Adding 1 to the month...\n";
        whoops.add_mon(1);
        std::cout << whoops << "\n";
    }
    catch(Date::Invalid) {
        std::cout << "Bad date!\n";
    }

    return 0;
}