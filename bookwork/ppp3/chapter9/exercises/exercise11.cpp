#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using std::string, std::cout, std::cin, std::vector;


class Point
{
    public:
        Point() : x{""}, y{""} { };
        Point(string xx, string yy) : x{xx}, y{yy} { };
        // getters
        string get_x() const { return x; };
        string get_y() const { return y; };
        string get_coordinates() const { return "(" + x + "," + y + ")"; };
        // setters
        void set_coordinates(string& xx, string& yy) { x = xx; y = yy; };

    private:
        string x {};
        string y {};
};

std::ostream& operator<<(std::ostream& os, const Point& p)
{
    return os << '(' << p.get_x() << ',' << p.get_y() << ')';
}

// This doesn't work, try again tomorrow.
std::istream& operator>>(std::istream& is, Point& p)
{
    char lpar, comma, rpar;
    string x, y;

    is >> lpar;
    if (lpar != '(') 
    {
        is.clear(std::ios::failbit);
        return is;
    }

    is >> x >> comma;
    if (comma != ',') 
    {
        is.clear(std::ios::failbit);
        return is;
    }

    is >> y >> rpar;
    if (rpar != ')') 
    {
        is.clear(std::ios::failbit);
        return is;
    }

    p.set_coordinates(x, y);
    return is;
}


int main()
{
    Point p1 {"80","80"};
    Point p2;

    cout << p1 << "\n";

    cin >> p2;

    cout << "You entered: " << p2 << "\n";

    return 0;
}

