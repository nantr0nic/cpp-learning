#include <iostream>
#include <stdexcept>
#include <exception>

enum class Month {
    jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

// Monday = 0, Tuesday = 1 and so on to Sunday = 6
enum class Day {
    monday, tuesday, wednesday, thursday, friday, saturday, sunday
};

int to_int(Month m)
{
    return static_cast<int>(m);
}

Month int_to_month(int x)
{
    if (x<to_int(Month::jan) || to_int(Month::dec)<x)
    {
        throw std::runtime_error("Invalid month!");
    }
    return Month{x};
}

std::ostream& operator<<(std::ostream& os, Month mm)
{
    switch(mm)
    {
        case Month::jan: return os << "January";
        case Month::feb: return os << "February";
        case Month::mar: return os << "March";
        case Month::apr: return os << "April";
        case Month::may: return os << "May";
        case Month::jun: return os << "June";
        case Month::jul: return os << "July";
        case Month::aug: return os << "August";
        case Month::sep: return os << "September";
        case Month::oct: return os << "October";
        case Month::nov: return os << "November";
        case Month::dec: return os << "December";
        default: return os << "Invalid month";
    }
}

int main()
{
    try {
        Month m1 = Month::feb;
        // Month m2 = feb;             // error: feb is not in scope
        // Month m3 = 7;               // error: can't assign an int to a Month
        Month m4 = Month{7};           // OK: explicit conversion
        Month m5 {7};                  // OK: explicit initialization

        // int x1 = m1;         // error: can't assign a Month to an int
        // int x2 = int{m1};    // error: narrowing conversion
        int x3 = to_int(m1);    // convert Month to int
        std::cout << "x3 is " << x3 << "\n";

        int month_num = 0;
        std::cout << "Enter a number for a month\n >> ";
        std::cin >> month_num;
        Month mm = int_to_month(month_num);
        std::cout << "The month you entered was " << mm;
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
