#include <iostream>
#include <stdexcept>
#include <exception>
#include <vector>

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

        std::cout << "\nLet's increment the month three times.\n";
        ++mm;
        std::cout << "The month is now " << mm;
        ++mm;
        std::cout << "\nThe month is now " << mm;
        ++mm;
        std::cout << "\nThe month is now " << mm;
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
