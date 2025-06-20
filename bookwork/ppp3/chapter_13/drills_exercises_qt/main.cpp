#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

// "Drills"
double one(double) { return 1; }
double slope(double x) { return 0.5 * x; }
double square(double x) { return x * x; }
double sloping_cos(double x) { return cos(x) + slope(x); }

// Drills 13-21
struct Person
{
    string name {};
    int age {};
};

istream& operator>>(istream& is, Person& p)
{
    cout << "Name? >> ";
    is >> p.name;
    cout << "\nAge? >> ";
    is >> p.age;
    cout << "\n";
    return is;
}

ostream& operator<<(ostream& os, Person& p)
{
    os << "Name: " << p.name << "\n" << "Age: " << p.age << "\n";
    return os;
}

using namespace Graph_lib;
int main(int /*argc*/, char * /*argv*/[])
{
    // "Drills"
    Application app;

    constexpr int xmax = 600;
    constexpr int ymax = 600;
    Simple_window win {{ 100, 100 }, xmax, ymax, "Function graphs"};

    // #2 -- draw these axes
    Axis x {Axis::x, Point{100, ymax / 2}, 400, 20, "1 == 20 pixels"};
    Axis y {Axis::y, Point{xmax / 2, 500}, 400, 20, "1 == 20 pixels"};
    x.set_color(Color::red);
    y.set_color(Color::red);
    win.attach(x);
    win.attach(y);

    // #3 graph one()
    // This doesn't end up on the appropriate notch because of the default scale
    // Function ex3 {one, -10, 11, {300, 300}, 400};
    // win.attach(ex3);

    // #4 graph one() but with x/y scaling
    // This does end up on the appropriate notch
    Function ex4 {one, -10, 11, {300, 300}, 400, 20, 20};
    win.attach(ex4);

    // #6
    constexpr double r1 { -10 };
    constexpr double r2 { 11 };
    constexpr Point origin { 300, 300 };
    constexpr int count { 400 };
    constexpr double xscale { 20 };
    constexpr double yscale { 20 };

    // #7
    Function ex7 {slope, r1, r2, origin, count, xscale, yscale};
    win.attach(ex7);

    // #8
    Text ex7_label {Point{ex7.point(0)}, "0.5x"};
    win.attach(ex7_label);

    // #9
    Function ex9 {square, r1, r2, origin, count, xscale, yscale};
    win.attach(ex9);

    // #10 + #11
    Function ex10 {[](double x) { return cos(x); }, r1, r2, origin, count, xscale, yscale};
    ex10.set_color(Color::blue);
    win.attach(ex10);

    // #12
    Function ex12 {sloping_cos, r1, r2, origin, count, xscale, yscale};
    win.attach(ex12);

    // Drills 13-21
    // #14
    Person ex14;
    ex14.name = "Goofy";
    ex14.age = 63;
    cout << "Name: " << ex14.name << "\n" << "Age: " << ex14.age << "\n";


    win.wait_for_button();
}
