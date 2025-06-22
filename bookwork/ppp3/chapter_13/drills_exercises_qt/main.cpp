#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

// "Drills"
double one(double) { return 1; }
double slope(double x) { return 0.5 * x; }
double square(double x) { return x * x; }
double sloping_cos(double x) { return cos(x) + slope(x); }

// Drills 13-21 are in a separate file.

// Exercises
//  Exercise 1
int fac(int n)
// factorial n!
{
    /*
     * I prefer this recursive version to the iterative version because
     * 1. It is more intuitive to how I conceive of factorials
     * 2. It is 'cleaner' and simpler syntax-wise
     * 3. Subtracting the 'while' condition removes a conceptual step
     * 4. The iterative version required declaring an int-type that this
     *      recursive version doesn't -- therefore it's theoretically more
     *      performative (I think).
    */
    return n > 1 ? n * fac(n - 1) : 1;
}

//  Exercise 2
class Fctn : public Open_polyline
{
public:
    Fctn(std::function<double(double)> f, double r1, double r2, Point xy, int count = 100, double xscale = 25, double yscale = 25);

    void fctn_construction();
    void reset_function(const std::function<double(double)> new_f);
    void reset_range(const double r1, const double r2);
    void reset_origin(const Point& p);
    void reset_count(const int n);
    void reset_xscale(const double x);
    void reset_yscale(const double y);

private:
    std::function<double(double)> m_f;
    double range1{};
    double range2{};
    Point origin;
    int n_count{};
    double m_xscale{};
    double m_yscale{};
};

// Exercise 5
double leib_series(int k)
{
    return ( (pow(-1, k)) / (2 * k + 1) );
}

// Exercise 6
struct Bar_graph : Shape
{
public:
    Bar_graph(Point origin, int width, int height)
        : m_origin { origin }, m_width { width }, m_height { height }
    { }

    void add_value(double val, string label = "", const Color& col = Color::invisible);

    void draw_specifics(Painter& painter) const override;

private:
    Point m_origin {};
    int m_width {};
    int m_height {};

    vector<double> values;
    vector<string> labels;
    vector<Color> colors;

    void determine_tallest();
    int determine_bar_height(double greatest_value, double value) const;
};

using namespace Graph_lib;
int main(int /*argc*/, char * /*argv*/[])
{
    // "Drills"
    Application app;

    // constexpr int xmax = 600;
    // constexpr int ymax = 600;
    // Simple_window win {{ 100, 100 }, xmax, ymax, "Function graphs"};

    // // #2 -- draw these axes
    // Axis x {Axis::x, Point{100, ymax / 2}, 400, 20, "1 == 20 pixels"};
    // Axis y {Axis::y, Point{xmax / 2, 500}, 400, 20, "1 == 20 pixels"};
    // x.set_color(Color::red);
    // y.set_color(Color::red);
    // win.attach(x);
    // win.attach(y);

    // // #3 graph one()
    // // This doesn't end up on the appropriate notch because of the default scale
    // // Function ex3 {one, -10, 11, {300, 300}, 400};
    // // win.attach(ex3);

    // // #4 graph one() but with x/y scaling
    // // This does end up on the appropriate notch
    // Function ex4 {one, -10, 11, {300, 300}, 400, 20, 20};
    // win.attach(ex4);

    // // #6
    // constexpr double r1 { -10 };
    // constexpr double r2 { 11 };
    // constexpr Point origin { 300, 300 };
    // constexpr int count { 400 };
    // constexpr double xscale { 20 };
    // constexpr double yscale { 20 };

    // // #7
    // Function ex7 {slope, r1, r2, origin, count, xscale, yscale};
    // win.attach(ex7);

    // // #8
    // Text ex7_label {Point{ex7.point(0)}, "0.5x"};
    // win.attach(ex7_label);

    // // #9
    // Function ex9 {square, r1, r2, origin, count, xscale, yscale};
    // win.attach(ex9);

    // // #10 + #11
    // Function ex10 {[](double x) { return cos(x); }, r1, r2, origin, count, xscale, yscale};
    // ex10.set_color(Color::blue);
    // win.attach(ex10);

    // // #12
    // Function ex12 {sloping_cos, r1, r2, origin, count, xscale, yscale};
    // win.attach(ex12);

    /****************************
     *      Exercises Below     *
     ****************************
    */

    // constexpr int xmax = 600;
    // constexpr int ymax = 600;
    // Simple_window win {{ 100, 100 }, xmax, ymax, "Chapter 13 Exercises"};


    // Axis x {Axis::x, Point{100, ymax / 2}, 400, 20, "1 == 20 pixels"};
    // Axis y {Axis::y, Point{xmax / 2, 500}, 400, 20, "1 == 20 pixels"};
    // x.set_color(Color::red);
    // y.set_color(Color::red);
    // win.attach(x);
    // win.attach(y);

    // constexpr double r1 { -10 };
    // constexpr double r2 { 11 };
    // constexpr Point origin { 300, 300 };
    // constexpr int count { 400 };
    // constexpr double xscale { 20 };
    // constexpr double yscale { 20 };

    // Fctn ex4 {sloping_cos, r1, r2, origin, count, xscale, yscale};
    // win.attach(ex4);
    // win.wait_for_button();

    // ex4.reset_range(-6, 7);
    // ex4.reset_origin({ 200, 200 });
    // ex4.reset_count(10);

    // Exercise 5
    /*
     * I wrote the following code but it wasn't graphically representing the
     * exercise succesfully because of the need for convergence graphs to be
     * iteratively drawn. I required the help of AI to figure out the correct
     * solution (below).
    */
    // for (int n = 0; n < 50; ++n)
    // {
    //     Fctn lseries {[](int k) { return (pow(-1, k)) / (2 * k + 1); }, r1, r2, origin, count, xscale, yscale};
    //     win.attach(lseries);
    //     win.wait_for_button();
    //     win.detach(lseries);
    // }

    // // Function that calculates the partial sum of Leibniz series up to n terms
    // auto leibniz_partial_sum = [](double n_terms) {
    //     double sum{0.0};
    //     int n = static_cast<int>(n_terms);
    //     for (int k = 0; k < n; ++k) {
    //         sum += (pow(-1, k)) / (2 * k + 1);
    //     }
    //     return sum;
    // };
    // // Then animate by showing different numbers of terms
    // for (int n = 1; n <= 10; ++n) {
    //     // Create a function that returns the n-th partial sum for any x
    //     auto current_sum = [n, &leibniz_partial_sum](double) {
    //         return leibniz_partial_sum(n);
    //     };

    //     Fctn convergence{current_sum, r1, r2, origin, count, xscale, yscale};
    //     win.attach(convergence);
    //     win.wait_for_button();
    //     win.detach(convergence);
    // }

    // Bar_graph test
    Simple_window win {{ 100, 100}, 800, 600, "Bar_graph test"};

    Bar_graph test {{ 50, 500 }, 600, 400};

    win.attach(test);


    win.wait_for_button();
}

///////// Fctn ////////////

Fctn::Fctn(std::function<double(double)> f, double r1, double r2, Point xy, int count, double xscale, double yscale)
    : m_f{f}, range1{r1}, range2{r2}, origin{xy}, n_count{count}, m_xscale{xscale}, m_yscale{yscale}
{
    fctn_construction();
}

void Fctn::fctn_construction()
{
    if (range2 - range1 <= 0)
        error("bad graphing range");
    if (n_count <= 0)
        error("non-positive graphing count");
    double dist = (range2 - range1) / n_count;
    double r = range1;
    for (int i = 0; i < n_count; ++i) {
        add(Point{origin.x + int(r * m_xscale), origin.y - int(m_f(r) * m_yscale)});
        r += dist;
    }
}

void Fctn::reset_function(const std::function<double(double)> new_f)
{
    m_f = new_f;
    clear_points();
    fctn_construction();
}

void Fctn::reset_range(const double r1, const double r2)
{
    range1 = r1;
    range2 = r2;
    clear_points();
    fctn_construction();
}

void Fctn::reset_origin(const Point& p)
{
    origin = p;
    clear_points();
    fctn_construction();
}

void Fctn::reset_count(const int n)
{
    n_count = n;
    clear_points();
    fctn_construction();
}

void Fctn::reset_xscale(const double x)
{
    m_xscale = x;
    clear_points();
    fctn_construction();
}

void Fctn::reset_yscale(const double y)
{
    m_yscale = y;
    clear_points();
    fctn_construction();
}

///////// Bar_graph /////////

void Bar_graph::add_value(double val, string label, const Color& col)
{
    values.push_back(val);
    labels.push_back(label);
    colors.push_back(col);
}

int Bar_graph::determine_bar_height(double greatest_value, double value) const
{
    // The greatest value will match the height of the bar graph (for now)
    if (greatest_value == 0)
        return 0;
    return static_cast<int>((value / greatest_value) * m_height);
}

void Bar_graph::draw_specifics(Painter& painter) const
{
    if (values.empty())
    {
        // do nothing
    }
    else if (!values.empty())
    {
        // First, determine the greatest value in the vector because that value will
        // match the height of the bar graph specified by the user
        double greatest_value {};
        for (const auto& value : values)
        {
            if (value > greatest_value)
            {
                greatest_value = value;
            }
        }

        // This determines the width for the bars before the loop
        int rect_width = static_cast<int>(m_width / values.size());

        for (size_t i = 0; i < values.size(); ++i)
        {
            // Draw the bar
            int rect_height = determine_bar_height(greatest_value, values[i]);
            int rect_x = m_origin.x + (rect_width * i);
            int rect_y = m_origin.y - rect_height;
            painter.draw_rectangle(Point(rect_x, rect_y), rect_width, rect_height);

            // Deal with the label and color here
        }
    }
}
