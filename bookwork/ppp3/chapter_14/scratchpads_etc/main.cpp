#include "PPP/GUI.h"

using namespace Graph_lib;

// --------------------------------------------- //
// First example ("Drawing lines") in chapter 14
// --------------------------------------------- //

struct Lines_window : Window {
    Lines_window(Application& application, Point xy, int w, int h, const string& title);
    Open_polyline lines;        // making a lines object here (used in next())
    void wait_for_button();

private:
    Application* app = nullptr;
    Button quit_button;         // a Widget
    In_box next_xy;             // a Widget
    Out_box xy_out;             // a Shape
    void next();
    void quit();
};

Lines_window::Lines_window(Application& application, Point xy, int w, int h, const string& title)
    : Window{ xy, w, h, title }
    , app(&application)     // needed to make reference to application -- textbook typo?
    , quit_button{ Point{ x_max() - 70, 0 }, 70, 20, "Quit", [this]() { quit(); } }
    , next_xy{ Point{ 250, 0 }, 50, 20, "next xy:", [this]() { next(); } }
    , xy_out{ Point{ 10, 10 }, "current (x,y): "}
{
    attach(lines);
    attach(quit_button);

    next_xy.hide_buttons();         // a Qt input box comes with buttons -- hide them
    attach(next_xy);
    next_xy.show();                 // but do show the box itself

    xy_out.label.set_font_size(8);  // user a smaller than default font
    xy_out.data.set_font_size(8);
    attach(xy_out);
}

void Lines_window::quit()
{
    end_button_wait();      // don't wait anymore
    next_xy.dismiss();      // clean up
    app->quit();
}

void Lines_window::next()       // the action performed by next_xy when woken up
{
    if (next_xy.last_result() == In_box::accepted)  // check if value has changed
    {
        string s = next_xy.last_string_value();     // read coordinate pair
        istringstream iss{ s };
        int x = 0;
        char ch = 0;
        int y = 0;
        iss >> x >> ch >> y;
        lines.add(Point{ x, y });

        ostringstream oss;                          // update current position readout
        oss << '(' << x << ',' << y << ')';
        xy_out.put(oss.str());
    }
    next_xy.clear_last_result();
}

// ----- 14.5.2 ----- //
struct Color_window : Lines_window {
    Color_window(Application& app, Point xy, int w, int h, const string& title);

private:
    void change(Color c) { lines.set_color(c); }
    void change_line(Line_style l) { lines.set_style(l); }
    void hide_menu() { color_menu.hide(); lines_menu.hide(); menu_button.show(); }

    Button menu_button;
    Button lines_button;
    Menu color_menu;
    Menu lines_menu;
};

Color_window::Color_window(Application& app, Point xy, int w, int h, const string& title)
    : Lines_window{ app, xy, w, h, title }
    , menu_button{ Point{ x_max() - 80, 30 }, 80, 20, "color menu",
                  [&] { menu_button.hide(); color_menu.show(); } }
    , lines_button{ Point{ x_max() - 80, 60 }, 80, 20, "lines menu",
                   [&] { lines_button.hide(); lines_menu.show(); }}
    , color_menu{ Point{ x_max() - 70, 40 }, 70, 20, Menu::vertical, "color"}
    , lines_menu{ Point{ x_max() - 100, 80 }, 70, 20, Menu::vertical, "lines"}
{
    attach(color_menu);
    color_menu.attach(make_unique<Button>( Point{0,0}, 0, 0, "red", [&] { change(Color::red); } ));
    color_menu.attach(make_unique<Button>( Point{0,0}, 0, 0, "blue", [&] { change(Color::blue); } ));
    color_menu.attach(make_unique<Button>( Point{0,0}, 0, 0, "black", [&] { change(Color::black); } ));

    attach(lines_menu);
    lines_menu.attach(make_unique<Button>( Point{0,0}, 0, 0, "dash", [&] { change_line(Line_style::dash); }));
    lines_menu.attach(make_unique<Button>( Point{0,0}, 0, 0, "dot", [&] { change_line(Line_style::dot); }));
    lines_menu.attach(make_unique<Button>( Point{0,0}, 0, 0, "solid", [&] { change_line(Line_style::solid); }));

    attach(menu_button);
    attach(lines_button);
    hide_menu();
}



int main()
{
    try
    {
        // Lines/Color _window
        Application app;                                                // create a GUI application
        Color_window win {app, Point{ 100, 100 }, 600, 400, "lines"};   // our window
        app.gui_main();                                                 // start the GUI application

        // // ----- 14.6 "Simple animation" ----- //
        // Application app;
        // Window w{ 140, 240, "Traffic light" };

        // Rectangle r{ { 10,10 }, 120, 220 };
        // r.set_fill_color(Color::black);

        // Circle red{ {70, 50}, 30};
        // Circle amber{ {70, 120}, 30};
        // Circle green{ {70, 190}, 30};

        // w.attach(r);
        // w.attach(red);
        // w.attach(amber);
        // w.attach(green);

        // const int second = 1000;
        // const int yellow_delay = 2 * second;
        // const int red_green_delay = 4 * second;

        // while (true)
        // {
        //     for (int i = 0; i < 3; ++i)
        //     {
        //         red.set_fill_color(Color::red);
        //         w.timer_wait(red_green_delay);

        //         amber.set_fill_color(Color::yellow);
        //         w.timer_wait(yellow_delay);

        //         red.set_fill_color(Color::black);
        //         amber.set_fill_color(Color::black);
        //         green.set_fill_color(Color::green);
        //         w.timer_wait(red_green_delay);
        //         amber.set_fill_color(Color::yellow);
        //         green.set_fill_color(Color::black);
        //         w.timer_wait(yellow_delay);

        //         amber.set_fill_color(Color::black);
        //     }
        // }

        return 0;                                                       // I changed this to 'return 0'
    }
    catch(exception& e)
    {
        cerr << "exception: " << e.what() << '\n';
        return 1;
    }
    catch(...)
    {
        cerr << "Some exception\n";
        return 2;
    }
}

