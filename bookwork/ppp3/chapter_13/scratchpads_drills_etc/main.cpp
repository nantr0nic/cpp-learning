#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

// 13.2 functions for graphs
double one(double) { return 1; }
double slope(double x) { return 0.5 * x; }
double square(double x) { return x * x; }
// 13.3
double dcos(double d) { return cos(d); }
double sloping_cos(double x) { return cos(x) + slope(x); }
double dlog(double d) { return log(d); }
double dsin(double d) { return sin(d); }
double dexp(double d) { return exp(d); }



using namespace Graph_lib;
int main(int /*argc*/, char * /*argv*/[])
{
    Application app;

    // Constant expressions for 13.2 function graphs
    constexpr int xmax = 600;           // window size
    constexpr int ymax = 400;

    constexpr int x_orig = xmax / 2;    // position of (0,0) is center of window
    constexpr int y_orig = ymax / 2;
    constexpr Point orig { x_orig, y_orig };

    constexpr int r_min = -10;          // range [-10:11)
    constexpr int r_max = 11;

    constexpr int n_points = 400;       // number of points used in range

    constexpr int x_scale = 30;         // scaling factors
    constexpr int y_scale = 30;

    Simple_window win {Point{ 100, 100 }, xmax, ymax, "Three functions"};

    // 3 functions
    Function s {one, r_min, r_max, orig, n_points, x_scale, y_scale};
    Function s2 {slope, r_min, r_max, orig, n_points, x_scale, y_scale};
    Function s3 {square, r_min, r_max, orig, n_points, x_scale, y_scale};
    win.attach(s);
    win.attach(s2);
    win.attach(s3);

    // Label the functions
    Text ts {Point{ 100, y_orig - 40 }, "one"};
    Text ts2 {Point{ 100, y_orig + y_orig / 2 - 20 }, "0.5*x"};
    Text ts3 {Point{ x_orig - 100, 20 }, "x*x"};
    win.attach(ts);
    win.attach(ts2);
    win.attach(ts3);
    win.set_label("Function graphing: label functions");

    // Axes
    constexpr int xlength = xmax - 40;  //  make the axis a bit smaller than the window
    constexpr int ylength = ymax - 40;

    Axis x {Axis::x, Point{ 20, y_orig }, xlength, xlength/x_scale, "one notch == 1"};
    Axis y {Axis::y, Point{ x_orig, ylength + 20}, ylength, ylength/y_scale, "one notch == 1"};
    x.set_color(Color::red);
    y.set_color(Color::red);
    win.attach(x);
    win.attach(y);

    // Cosine graphs
    Function s4 {dcos, r_min, r_max, orig, 400, 30, 30};
    s4.set_color(Color::blue);
    win.attach(s4);

    // Function s5 {sloping_cos, r_min, r_max, orig, 400, 30, 30};
    // s5 but using a lamba expression VVV
    Function s5 {[](double x) { return cos(x)+slope(x); }, r_min, r_max, orig, 400, 30, 30};
    s5.set_color(Color::green);
    win.attach(s5);

    x.label.move(-160, 0);
    x.notches.set_color(Color::dark_red);

    Function f1 {dlog, 0.000001, r_max, orig, 200, 30, 30};
    Function f2 {dsin, r_min, r_max, orig, 200, 30, 30};
    f2.set_color(Color::blue);
    Function f3 {dcos, r_min, r_max, orig, 200, 30, 30};
    Function f4 {dexp, r_min, r_max, orig, 200, 30, 30};
    win.attach(f1);
    win.attach(f2);
    win.attach(f3);
    win.attach(f4);

    win.wait_for_button();
}
