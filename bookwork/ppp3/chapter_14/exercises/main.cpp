#include "PPP/GUI.h"
#include "PPP/GUI_private.h"
#include "PPP/Graph.h"
#include "PPP/Window.h"
#include "PPP/Simple_window.h"

#include <chrono>

using namespace Graph_lib;

// ----- Exercises 1 and 2 ----- //
struct My_window : Window {
public:
    My_window(Point xy, int w, int h, const string& title);
    ~My_window() { }
    void wait_for_next();

private:
    Button next_button;
    Button quit_button;
    // Exercise 2
    Button checkbutton_1;
    Button checkbutton_2;
    Button checkbutton_3;
    Button checkbutton_4;
    Circle circle;
};

// ----- Exercise 3 ----- //
struct Exercise3 {
private:
    inline int rand_int(int min, int max)
    {
        static default_random_engine ran;
        return uniform_int_distribution<>{min, max}(ran);
    }
    void move_rand() {
        int rand_x = rand_int(-25, 25);
        int rand_y = rand_int(-25, 25);
        ex3button.move(rand_x, rand_y);
        img.move(rand_x, rand_y);
    }
    string image_file {"/home/nantr0nic/code/cpp-learning/bookwork/ppp3/chapter_14/exercises/cpp.png"};

public:
    Exercise3(Simple_window& win);
    Image img;
    Button ex3button;
};

// ----- Exercise 4 ----- //

struct Triangle : Closed_polyline
{
public:
    Triangle(Point origin, int side)
    {
        add(origin);
        Point second{(origin.x + side), (origin.y)};
        add(second);
        Point third{(origin.x), (origin.y + side)};
        add(third);
    }
};

struct Shapes_window : Window
{
public:
    Shapes_window(Application& app, Point xy, int w, int h, const string& title);
    Vector_ref<Shape> shapes;

private:
    Application* app = nullptr;
    // Widgets
    In_box shape_xy;
    Menu shapes_menu;
    // User input
    void accept_xy();
    // This stores the Point for drawing the menu
    Point xy_loc {0, 0};
    // Drawing functions
    void draw_square();
    void draw_circle();
    void draw_triangle();
    // Vector_ref for storing shapes
    Vector_ref<Shape> user_shapes;

};

// ----- Exercise 6 ----- //
struct A_clock : Window
{
public:
    A_clock(int w=250, int h=250, const string& title = "Analogue Clock");

private:
    int hh, mm, ss;
    double pi {3.14159};

    Circle face;
    Line hour;
    Line minute;
    Line second;

    void update();
};

// ----- Exercise 7 ----- //
struct Fly_cpp : Window
{
public:
    Fly_cpp(int w=800, int h=600, const string& title = "Flying!!!");

private:
    string image_file {"/home/nantr0nic/code/cpp-learning/bookwork/ppp3/chapter_14/exercises/cpp.png"};
    Image img;

    Button start;
    Button stop;
    bool flying {true};

    void update();
    void change_state() { flying = !flying; };

    inline int rand_int(int min, int max)
    {
        static default_random_engine ran;
        return uniform_int_distribution<>{min, max}(ran);
    }
};

// ----- Exercise 8 ----- //
struct Converter : Window
{
public:
    Converter(int w=400, int h=150, const string& title = "Currency Converter");

private:
    string currency_file {"/home/nantr0nic/code/cpp-learning/bookwork/ppp3/chapter_14/exercises/currencies.txt"};
    In_box in_value;
    Out_box out_value;

    double in_vv;       // User input value
    double out_vv;      // Final converted output
    double in_c_vv;     // Input currency exchange
    double out_c_vv;    // Output currency exchange

    Menu currency_in_menu;
    Menu currency_out_menu;

    void convert();

    string in_currency {};
    string out_currency {};

    vector<string> currencies;
    vector<double> currency_values;
};

int main(int /*argc*/, char * /*argv*/[])
{
    Application app;
    // My_window win {{ 100, 100 }, 800, 600, "Chapter 14 Exercises 1 and 2"};
    // win.wait_for_next();

    // Simple_window win {{ 100, 100 }, 800, 600, "Chapter 14 Exercise 3"};
    // Exercise3 ex3 {win};
    // win.wait_for_button();

    // Shapes_window win {app, { 100, 100 }, 800, 600, "Shapes Window"};

    // // Exercise 6
    // A_clock clock {};

    // // Exercise 7
    // Fly_cpp fly {};

    // Exercise 8
    Converter conv {};


    app.gui_main();
}

// Exercises 1 & 2
// this might be a less than ideal technique but it demonstrates the concepts
// and techniques explained in Chapter 14 (e.g. this type of initialization
// and lambda expressions)
My_window::My_window(Point xy, int w, int h, const string& title)
    : Window(xy, w, h, title)
    , next_button(Point{ x_max() - 80, y_max() - 30 }, 70, 20, "Next", [] {})
    , quit_button(Point{ x_max() - 80, 0 }, 70, 20, "Quit", [this] { close(); })
    , checkbutton_1(Point{ 50, 50 }, 100, 100, "Move me", [this] { checkbutton_1.move(5, 5); })
    , checkbutton_2(Point{ 150, 150 }, 100, 100, "Hide Me", [this] { checkbutton_2.hide(); })
    , checkbutton_3(Point{ 50, 150 }, 100, 100, "Surprise...", [this] { this->set_label("Surprised?!"); })
    , checkbutton_4(Point{ 150, 50 }, 100, 100, "Don't overlap", [this] { this->attach(circle); })
    , circle(Point{ 250, 250 }, 50)
{
    circle.set_fill_color(Color::dark_cyan);
    attach(next_button);
    attach(quit_button);
    attach(checkbutton_1);
    attach(checkbutton_2);
    attach(checkbutton_3);
    attach(checkbutton_4);
}

void My_window::wait_for_next()
{
    get_impl().wait_for_button(&next_button);
}

// ----- Exercise 3 ----- //
// Using a different technique here with win being passed by reference
Exercise3::Exercise3(Simple_window& win)
    : img(Point{ 200, 50 }, image_file)
    , ex3button(Point{ 200, 200 }, 150, 150, "Exercise 3", [this] { this->move_rand(); })
{
    img.scale(150, 150);
    win.attach(img);
    win.attach(ex3button);
}

// ----- Exercise 4 ----- //
// Make an in box, user gives coordinates, menu appears at those coordinates,
// draw shape that's chosen at those coordinates
Shapes_window::Shapes_window(Application& application, Point xy, int w, int h, const string& title)
    : Window{ xy, w, h, title }
    , app(&application)
    , shape_xy(Point{ x_max() - 180, 20 }, 40, 20, "Enter x,y:", [this] { accept_xy(); })
    , shapes_menu(Point{ 0,0 }, 60, 20, Menu::vertical, "Shapes")
{
    shape_xy.hide_buttons();
    attach(shape_xy);
    shape_xy.show();

    shapes_menu.attach(make_unique<Button>(Point{0,0}, 0, 0, "Square", [this] { draw_square(); }));
    shapes_menu.attach(make_unique<Button>(Point{0,0}, 0, 0, "Circle", [this] { draw_circle(); }));
    shapes_menu.attach(make_unique<Button>(Point{0,0}, 0, 0, "Triangle", [this] { draw_triangle(); }));
}

void Shapes_window::accept_xy()
{
    if (shape_xy.last_result() == In_box::accepted)
    {
        // Assign the user's input and parse it with istringstream
        string input = shape_xy.last_string_value();
        istringstream iss{ input };
        // These variables are for parsing
        int x {};
        char c {};
        int y {};
        iss >> x >> c >> y;
        // Set xy coordinates for shape drawing functions
        xy_loc.x = x;
        xy_loc.y = y;
        // Set menu's coordinates to user's input then attach + show
        shapes_menu.loc.x = x;
        shapes_menu.loc.y = y;
        attach(shapes_menu);
        shapes_menu.show();
    }
    shape_xy.clear_last_result();
}

void Shapes_window::draw_square()
{
    shapes_menu.hide();
    user_shapes.push_back(make_unique<Rectangle>(xy_loc, 50, 50));
    this->attach(user_shapes[user_shapes.size() - 1]);
}

void Shapes_window::draw_circle()
{
    shapes_menu.hide();
    user_shapes.push_back(make_unique<Circle>(xy_loc, 25));
    this->attach(user_shapes[user_shapes.size() - 1]);
}

void Shapes_window::draw_triangle()
{
    shapes_menu.hide();
    user_shapes.push_back(make_unique<Triangle>(xy_loc, 50));
    this->attach(user_shapes[user_shapes.size() - 1]);
}

// ----- Exercise 6 ----- //
A_clock::A_clock(int w, int h, const string& title)
    : Window(w, h, title)
    , face(Point{x_max() / 2, y_max() / 2}, 100)
    , hour(face.center(), face.point(0))
    , minute(face.center(), face.point(0))
    , second(face.center(), face.point(0))
{
    // Set colors
    face.set_fill_color(Color::black);
    hour.set_color(Color::magenta);
    minute.set_color(Color::white);
    second.set_color(Color::cyan);
    // Attach the shapes
    attach(face);
    attach(hour);
    attach(minute);
    attach(second);
    // Create the timer that will update the clock
    while (true)
    {
        update();
        timer_wait(1000);
    }
}

void A_clock::update()
{
    // Get the current time and update the h/m/s
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto* tm = localtime(&time_t);

    int hh = tm->tm_hour % 12;    // 12-hour format
    int mm = tm->tm_min;
    int ss = tm->tm_sec;

    // Redraw the lines accordingly

    // Determine the end-points for each hand
    // Calculate the angles
    double hour_angle = (30 * hh) + (mm * 0.5);
    double minute_angle = 6 * mm;
    double second_angle = 6 * ss;

    // End-points
    /* I added update_point to Shape for efficiency. */
    int hour_x = face.center().x + static_cast<int>((face.radius() / 2) * sin(hour_angle * pi / 180.0));
    int hour_y = face.center().y - static_cast<int>((face.radius() / 2) * cos(hour_angle * pi / 180.0));
    hour.update_point(1, Point(hour_x, hour_y));

    int minute_x = face.center().x + static_cast<int>((face.radius() - (face.radius() * .2)) * sin(minute_angle * pi / 180.0));
    int minute_y = face.center().y - static_cast<int>((face.radius() - (face.radius() * .2)) * cos(minute_angle * pi / 180.0));
    minute.update_point(1, Point(minute_x, minute_y));

    int second_x = face.center().x + static_cast<int>((face.radius()) * sin(second_angle * pi / 180.0));
    int second_y = face.center().y - static_cast<int>((face.radius()) * cos(second_angle * pi / 180.0));
    second.update_point(1, Point(second_x, second_y));
}

// ----- Exercise 7 ----- //
Fly_cpp::Fly_cpp(int w, int h, const string& title)
    : Window(w, h, title)
    , img(Point{x_max() / 2, y_max() / 2}, image_file)
    , start(Point{x_max() - 70, 0}, 50, 20, "Start", [this] { change_state(); })
    , stop(Point{(x_max() - 70), 25}, 50, 20, "Stop", [this] { change_state(); })
{
    // Attach buttons
    attach(start);
    attach(stop);
    // Scale and attach image
    img.scale(100, 100);
    attach(img);
    // Flying loop
    while (true)
    {
        timer_wait(250);
        update();
    }
}

void Fly_cpp::update()
{
    if (flying)
    {
        int move_x = rand_int(-10, 10);
        int move_y = rand_int(-10, 10);
        img.move(move_x, move_y);
    }
}

// ----- Exercise 8 ----- //

Converter::Converter(int w, int h, const string& title)
    : Window(w, h, title)
    , in_value(Point{60, 0}, 50, 20, "Input Value:", [this] { convert(); })
    , out_value(Point{(x_max() / 2), 0}, "Output Value", Out_box::vertical)
    , currency_in_menu(Point{0,0}, 50, 20, Menu::vertical, "Input Currency")
    , currency_out_menu(Point{(x_max() - 55), 0}, 50, 20, Menu::vertical, "Output Currency")
{
    // Initialize strings here
    in_currency = "USD";
    out_currency = "EUR";
    // In box
    in_value.hide_buttons();
    attach(in_value);
    in_value.show();
    // Out box
    out_value.label.set_font_size(8);
    out_value.data.set_font_size(8);
    attach(out_value);
    // Currency in menu
    currency_in_menu.attach(make_unique<Button>(Point{0,0}, 0, 0, "USD", [this] { in_currency = "USD"; }));
    currency_in_menu.attach(make_unique<Button>(Point{0,0}, 0, 0, "GBP", [this] { in_currency = "GBP"; }));
    currency_in_menu.attach(make_unique<Button>(Point{0,0}, 0, 0, "ISK", [this] { in_currency = "ISK"; }));
    currency_in_menu.attach(make_unique<Button>(Point{0,0}, 0, 0, "CUP", [this] { in_currency = "CUP"; }));
    currency_in_menu.attach(make_unique<Button>(Point{0,0}, 0, 0, "EUR", [this] { in_currency = "EUR"; }));
    attach(currency_in_menu);
    // Currency out menu
    currency_out_menu.attach(make_unique<Button>(Point{0,0}, 0, 0, "USD", [this] { out_currency = "USD"; }));
    currency_out_menu.attach(make_unique<Button>(Point{0,0}, 0, 0, "GBP", [this] { out_currency = "GBP"; }));
    currency_out_menu.attach(make_unique<Button>(Point{0,0}, 0, 0, "ISK", [this] { out_currency = "ISK"; }));
    currency_out_menu.attach(make_unique<Button>(Point{0,0}, 0, 0, "CUP", [this] { out_currency = "CUP"; }));
    currency_out_menu.attach(make_unique<Button>(Point{0,0}, 0, 0, "EUR", [this] { out_currency = "EUR"; }));
    attach(currency_out_menu);

    // Get the currency information from file and set it up here
    // We will add them to vectors to make calculation easier
    ifstream ifs {currency_file};
    if (ifs.is_open())
    {
        string line;
        while (getline(ifs, line))
        {
            istringstream iss {line};
            string curr {};
            char c {};
            double value {};
            iss >> curr >> c >> value;
            currencies.push_back(curr);
            currency_values.push_back(value);
        }
    }
}

void Converter::convert()
{
    for (size_t i = 0; i < currencies.size(); ++i)
    {
        if (in_currency == currencies[i])
        {
            in_c_vv = currency_values[i];
        }
        if (out_currency == currencies[i])
        {
            out_c_vv = currency_values[i];
        }
    }
    if (in_value.last_result() == In_box::accepted)
    {
        // Get the input value
        string s = in_value.last_string_value();
        istringstream vss { s };
        vss >> in_vv;
        // Conversion formula
        out_vv = (in_vv * (1/in_c_vv)) * out_c_vv;
        // Put the output
        ostringstream oss;
        oss << out_vv;
        out_value.put(oss.str());
    }
}
