#include "PPP/GUI.h"
#include "PPP/GUI_private.h"
#include "PPP/Graph.h"
#include "PPP/Window.h"
#include "PPP/Simple_window.h"

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

int main(int /*argc*/, char * /*argv*/[])
{
    Application app;
    // My_window win {{ 100, 100 }, 800, 600, "Chapter 14 Exercises 1 and 2"};
    // win.wait_for_next();

    // Simple_window win {{ 100, 100 }, 800, 600, "Chapter 14 Exercise 3"};
    // Exercise3 ex3 {win};
    // win.wait_for_button();

    Shapes_window win {app, { 100, 100 }, 800, 600, "Shapes Window"};


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
