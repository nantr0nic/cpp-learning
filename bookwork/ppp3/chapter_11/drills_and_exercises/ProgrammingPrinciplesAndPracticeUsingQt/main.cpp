#include "PPP/Graph.h"
#include "PPP/Simple_window.h"

using namespace Graph_lib;
int main(int /*argc*/, char * /*argv*/[])
{
    /*
     * Below are the 5 drills. The exercises from the end of the chapter begin
     * on line 80 and continue beneath.
     */

    // Application app;
    // Simple_window win {Point{ 150, 150 }, 800, 1000, "Chapter 11 Drills"};

    // // Drill #2
    // int x_max = 800;
    // int y_max = 800;
    // int grid_x = 100;
    // int grid_y = 100;
    // Lines grid;
    // for (int i {0}; i <= x_max; i += grid_x)
    // {
    //     grid.add(Point{ i, 0 }, Point{ i, 800 });
    // }
    // for (int i {0}; i <= y_max; i += grid_y)
    // {
    //     grid.add(Point{ 0, i }, Point{ 800, i });
    // }
    // win.attach(grid);
    // win.wait_for_button();

    // // Drill 3
    // Vector_ref<Rectangle> red_squares {};
    // for (int i {0}; i < 8; ++i)
    // {
    //     int top_left = (i * 100);
    //     int bottom_right = (top_left + 100);
    //     red_squares.push_back(make_unique<Rectangle>(Point{ top_left, top_left }, Point{ bottom_right, bottom_right}));
    // }
    // for (int i {0}; i < red_squares.size(); ++i)
    // {
    //     red_squares[i].set_fill_color(Color::red);
    // }
    // for (const auto& square : red_squares)
    // {
    //     win.attach(*square);
    // }

    // win.wait_for_button();

    // // Drill 4
    // std::string image_file = "/home/nantr0nic/code/cpp-learning/bookwork/ppp3/chapter_11/drills_and_exercises/ProgrammingPrinciplesAndPracticeUsingQt/cpp.jpg";
    // Image cpp1 {Point{ 600, 0 }, image_file};
    // Image cpp2 {Point{ 0, 600 }, image_file};
    // Image cpp3 {Point{ 200, 0 }, image_file};
    // cpp1.scale(200, 200);
    // cpp2.scale(200, 200);
    // cpp3.scale(200, 200);
    // win.attach(cpp1);
    // win.attach(cpp2);
    // win.attach(cpp3);
    // win.wait_for_button();

    // // Drill 5
    // std::string image_file2 = "/home/nantr0nic/code/cpp-learning/bookwork/ppp3/chapter_11/drills_and_exercises/ProgrammingPrinciplesAndPracticeUsingQt/qtlogo.jpg";
    // Image qtlogo {Point{ 0, 0 }, image_file2};
    // win.attach(qtlogo);
    // win.put_on_top(qtlogo);
    // win.wait_for_button();
    // int move_x = grid_x;
    // int move_y = 0;
    // for (int i {0}; i < 7; ++i)
    // {
    //     qtlogo.move(move_x, move_y);
    //     win.wait_for_button();
    // }
    // win.wait_for_button();

    ///// ------------- Exercises --------------- /////

    Application app;
    Simple_window win {Point{ 150, 150 }, 1024, 768, "Chapter 11 Exercises"};

    Closed_polyline cpl {
        { 200, 0 }, { 50, 150 }, { 350, 300 }, { 50, 450 }, { 200, 600 }
    };

    cpl.set_color(Color::red);
    cpl.set_style(Line_style(Line_style::solid,3));

    win.attach(cpl);

    win.wait_for_button();


}
