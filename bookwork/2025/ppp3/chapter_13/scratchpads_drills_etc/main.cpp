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
// 13.5
// We're using stl's pow() but will need to define a function for factorials
long double fac(long double n)      // factorial(n); n!
{
    int r = 1;
    while (n > 1)
    {
        r *= n;
        --n;
    }
    return r;
}
long double term(long double x, int n) { return std::pow(x, n) / fac(n); } // nth term of series
long double exp_n(long double x, int n)
{
    double sum = 0;
    for (int i = 0; i < n; ++i)
        sum += term(x, i);
    return sum;
}

// 13.6
struct Distribution
{
    int year;
    double young, middle, old;
};

class Scale         // data value to coordinate conversion
{
    int cbase;      // coordinate base
    int vbase;      // base of values
    double scale;
public:
    Scale(int b, int vb, double s) : cbase{ b }, vbase{ vb }, scale{ s } {}
    int operator()(double v) const { return cbase + (v-vbase) * scale; }
};

istream& operator>>(istream& is, Distribution& d)
// assume format: { year : young middle old }
{
    char ch1 = 0;
    char ch2 = 0;
    char ch3 = 0;
    Distribution dd;

    if (is >> ch1 >> dd.year
           >> ch2 >> dd.young >> dd.middle >> dd.old
        >> ch3)
    {
        if (ch1 != '{' || ch2 != ':' || ch3 != '}')
        {
            is.clear(ios_base::failbit);
        }
        else
        {
            d = dd;
        }
    }
    return is;
}

using namespace Graph_lib;
int main(int /*argc*/, char * /*argv*/[])
{
    Application app;

    // // Constant expressions for 13.2-13.5 function graphs
    // // Uncomment this section for any of the graphs before 13.6
    // constexpr int xmax = 600;           // window size
    // constexpr int ymax = 400;

    // constexpr int x_orig = xmax / 2;    // position of (0,0) is center of window
    // constexpr int y_orig = ymax / 2;
    // constexpr Point orig { x_orig, y_orig };

    // constexpr int r_min = -10;          // range [-10:11)
    // constexpr int r_max = 11;

    // //constexpr int n_points = 400;       // number of points used in range

    // constexpr int x_scale = 30;         // scaling factors
    // constexpr int y_scale = 30;

    // Simple_window win {Point{ 100, 100 }, xmax, ymax, "Chapter 13"};

    // // 3 functions
    // Function s {one, r_min, r_max, orig, n_points, x_scale, y_scale};
    // Function s2 {slope, r_min, r_max, orig, n_points, x_scale, y_scale};
    // Function s3 {square, r_min, r_max, orig, n_points, x_scale, y_scale};
    // win.attach(s);
    // win.attach(s2);
    // win.attach(s3);

    // // Label the functions
    // Text ts {Point{ 100, y_orig - 40 }, "one"};
    // Text ts2 {Point{ 100, y_orig + y_orig / 2 - 20 }, "0.5*x"};
    // Text ts3 {Point{ x_orig - 100, 20 }, "x*x"};
    // win.attach(ts);
    // win.attach(ts2);
    // win.attach(ts3);
    // win.set_label("Function graphing: label functions");

    // // Axes
    // // Uncomment this "Axes" section for any of the exercises prior to 13.6
    // constexpr int xlength = xmax - 40;  //  make the axis a bit smaller than the window
    // constexpr int ylength = ymax - 40;

    // Axis x {Axis::x, Point{ 20, y_orig }, xlength, xlength/x_scale, "x"};
    // Axis y {Axis::y, Point{ x_orig, ylength + 20}, ylength, ylength/y_scale, "y"};
    // x.set_color(Color::red);
    // y.set_color(Color::red);
    // win.attach(x);
    // win.attach(y);

    // // Cosine graphs
    // Function s4 {dcos, r_min, r_max, orig, 400, 30, 30};
    // s4.set_color(Color::blue);
    // win.attach(s4);

    // // Function s5 {sloping_cos, r_min, r_max, orig, 400, 30, 30};
    // // s5 but using a lamba expression VVV
    // Function s5 {[](double x) { return cos(x)+slope(x); }, r_min, r_max, orig, 400, 30, 30};
    // s5.set_color(Color::green);
    // win.attach(s5);

    // x.label.move(-160, 0);
    // x.notches.set_color(Color::dark_red);

    // Function f1 {dlog, 0.000001, r_max, orig, 200, 30, 30};
    // Function f2 {dsin, r_min, r_max, orig, 200, 30, 30};
    // f2.set_color(Color::blue);
    // Function f3 {dcos, r_min, r_max, orig, 200, 30, 30};
    // Function f4 {dexp, r_min, r_max, orig, 200, 30, 30};
    // win.attach(f1);
    // win.attach(f2);
    // win.attach(f3);
    // win.attach(f4);

    // // 13.5
    // Function real_exp { [](double x) { return std::exp(x); }, r_min, r_max, orig, 200, x_scale, y_scale };
    // real_exp.set_color(Color::blue);
    // win.attach(real_exp);

    // // Graphing e^x
    // for (int n = 0; n < 50; ++n)
    // {
    //     ostringstream ss;
    //     ss << "exp approximation; n==" << n;
    //     win.set_label(ss.str());

    //     // get next approximation:
    //     // long helps but doesn't fix it totally
    //     Function e {[n](long double x) { return exp_n(x,n); }, r_min, r_max, orig, 200, x_scale, y_scale };

    //     win.attach(e);
    //     win.wait_for_button();
    //     win.detach(e);
    // }

    // ----------------------------------------------- //
    // ----------------------------------------------- //

    // 13.6
    constexpr int xmax = 600;       // window size
    constexpr int ymax = 400;

    constexpr int xoffset = 100;    // distance from left-hand side of window to y axis
    constexpr int yoffset = 60;     // distance from bottom of window to x axis

    constexpr int xspace = 40;      // space beyond axis
    constexpr int yspace = 40;

    constexpr int xlength = xmax - xoffset - xspace;    // length of axes
    constexpr int ylength = ymax - yoffset - yspace;

    // Use 1960 if you want to see data from 1960 to today and projected past
    //constexpr int base_year = 1960;
    constexpr int base_year = 2010;
    constexpr int end_year = 2040;

    constexpr double xscale = double(xlength) / (end_year - base_year);
    constexpr double yscale = double(ylength) / 100;
    Scale xs {xoffset, base_year, xscale};
    Scale ys {ymax-yoffset, 0, -yscale};


    Simple_window win { { 100, 100 }, xmax, ymax, "Aging Japan" };

    // Make the Axes
    // X-axis
    Axis x { Axis::x, Point{xoffset, ymax - yoffset}, xlength, (end_year-base_year)/5,
            "year  "
            "2010    2015      2020      2025      "
            "2030    2035      2040"
    };
    x.label.move(-100,0);
    x.label.set_font_size(10);

    // Y-axis
    Axis y { Axis::y, Point{xoffset, ymax - yoffset}, ylength, 10, "% of population"};

    int now = 2025;
    Line current_year {Point{xs(now), ys(0)}, Point{xs(now), ys(100)}};
    current_year.set_style(Line_style::dash);

    // Open the file
    // Use japanese-age-data1960.txt if you want to see 1960-today-projected
    string file_name = "/home/nantr0nic/code/cpp-learning/bookwork/ppp3/chapter_13/scratchpads_drills_etc/japanese-age-data.txt";
    ifstream ifs { file_name };

    if (!ifs)
    {
        Text err_label { Point{ 20, 20}, "Can't open file" };
        win.attach(err_label);
        win.wait_for_button();
        error("can't open ", file_name);
    }

    // Make the lines for ages
    Open_polyline children;
    Open_polyline adults;
    Open_polyline aged;

    // Deal with the data
    for (Distribution d; ifs >> d; )
    {
        if (d.year < base_year || end_year < d.year)
            error("year out of range");

        double all = d.young + d.middle + d.old;
        if (all - 100 > 1.5 || 100 - all > 1.5)     // take rounding errors into account
            error("percentages don't add up");

        const int x = xs(d.year);
        children.add(Point{ x, ys(d.young)});
        adults.add(Point{ x, ys(d.middle)});
        aged.add(Point{ x, ys(d.old)});
    }

    // Make graphs readable
    Text children_label {Point{20,children.point(0).y},"age 0−14"};
    children.set_color(Color::red);
    children_label.set_color(Color::red);
    children_label.set_font_size(10);
    children_label.set_style(Line_style::dash);

    Text adults_label {Point{20,adults.point(0).y},"age 15−64"};
    adults.set_color(Color::blue);
    adults_label.set_color(Color::blue);
    adults_label.set_font_size(10);

    Text aged_label {Point{20,aged.point(0).y},"age 65+"};
    aged.set_color(Color::dark_green);
    aged_label.set_color(Color::dark_green);
    aged_label.set_font_size(10);
    aged_label.set_style(Line_style::dashdotdot);

    win.attach(children);
    win.attach(adults);
    win.attach(aged);
    win.attach(children_label);
    win.attach(adults_label);
    win.attach(aged_label);
    win.attach(x);
    win.attach(y);
    win.attach(current_year);
    win.wait_for_button();


    win.wait_for_button();
}
