#include <iostream>
#include <string>
#include <sstream>

class Point
{
    public:
    Point get_coordinates(const std::string& s);
    
    private:
    unsigned int x;
    unsigned int y;
};

Point Point::get_coordinates(const std::string& s)   // extract {x,y} from "(x,y)"
{
    std::istringstream is {s};      // make a stream so that we can read from s
    Point xy;
    char left_paren, ch, right_paren;
    is >> left_paren >> xy.x >> ch >> xy.y >> right_paren;
    if (!is || left_paren != '(' || ch != ',' || right_paren != ')')
    {
        throw std::runtime_error("format error: " + s);
    }
    return xy;
}

int main()
{
    /* Example use:
    Point xy;
    auto c1 = xy.get_coordinates("(2,3)");
    auto c2 = xy.get_coordinates("( 200, 300) ");
    auto c3 = xy.get_coordinates("100,400");    // will throw error
    */

    /*
    ostringstream constructed strings by concatenation

    int seq_no = get_next_number();
    std::ostringstream name;
    name << "myfile" << seq_no << ".log";
    ofstream logfile {name.str()};

    name << "myfile" << setw(6) << setfill('0') << seq_no << ".log"; // myfile000017.log
    */
    return 0;
}
