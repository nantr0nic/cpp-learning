// methods

#include <cstdio>

struct ClockOfTheLongNow {
    void add_year() {
        year++;
    }
    bool set_year(int new_year) { // "setter"
        if (new_year < 2024) return false;
        year = new_year;
        return true;
    }
    int get_year() { // "getter"
        return year;
    }
    private: 
    int year;
};

/* using 'class': 

class ClockOfTheLongNow {
    int year;
    public:
    void add_year() {
    ...
    etc.
    }
}
* Using 'struct' the public stuff comes first, then you declare the private stuff.
* Using 'class' the private stuff comes first, then you declare the public stuff.
*/

int main() {
    ClockOfTheLongNow clock;
    if(!clock.set_year(2018)) { // will fail, 2018 < 2024
    clock.set_year(2024);
    }
    clock.add_year();
    printf("year: %d", clock.get_year());
}