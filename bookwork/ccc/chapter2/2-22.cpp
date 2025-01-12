// methods

#include <cstdio>

struct ClockOfTheLongNow {
    ClockOfTheLongNow(int year_in) { // constructor
        if(!set_year(year_in)) {
            year = 2024;
        }
    }
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

int main() {
    ClockOfTheLongNow clock{ 2020 };
    printf("Default year: %d\n", clock.get_year());
    if(!clock.set_year(2018)) { // will fail, 2018 < 2024
    clock.set_year(2024);
    }
    clock.add_year();
    printf("year: %d", clock.get_year());
}