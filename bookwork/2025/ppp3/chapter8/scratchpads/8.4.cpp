// simple Date

struct Date {
    int y, m, d;                // year, month, day
    Date(int y, int m, int d);  // check for valid date and initialize
    void add_day(int n);        // increase the Date by n days
};

void init_day(Date& dd, int y, int m, int d)
{
    dd.y = y;
    dd.m = m;
    dd.d = d;
}

void add_day(Date& dd, int n)
{
    dd.d += n;
}

int main()
{
    // Date birthday;                   error: birthday not initialized
    Date today {4,14,2025};             // oops! run-time error
    Date last {2005,12,31};             // OK (colloquial style)
    Date next = {2014, 2, 14};          // also OK (slightly verbose)
    Date Beethoven = Date {1770,12,16}; // also OK (verbose style)

    return 0;
}