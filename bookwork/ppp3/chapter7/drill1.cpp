#include <iostream>

void swap_v(int a, int b) { int temp; temp = a; a = b; b = temp; }
void swap_r(int& a, int& b) { int temp; temp = a; a = b; b = temp; }
void swap_cr(const int& a, const int& b) { 
    int temp; 
    temp = a;
    // won't compile with the following lines... 
    //a = b; 
    //b = temp; 
}
void swap_auto(auto& a, auto& b) { auto temp = 0; temp = a; a = b; b = temp; }

int main()
{
    int x = 7;
    int y = 9;
    std::cout << "x / y = " << x << " / " << y << "\n";
    swap_v(x, y);
    std::cout << "(swap_v) x / y = " << x << " / " << y << "\n";    // doesn't swap x and y in main scope
    swap_r(x, y);
    std::cout << "(swap_r) x / y = " << x << " / " << y << "\n";    // actually swaps x and y in main scope
    swap_v(7,9);
    //swap_r(7,9);    // doesn't compile because must value of ref must be an lvalue
    const int cx = 7;
    const int cy = 9;
    std::cout << "cx / cy = " << cx << " / " << cy << "\n";
    swap_v(cx, cy);
    std::cout << "swap_v cx / cy = " << cx << " / " << cy << "\n";
    // swap_r(cx, cy);  // doesn't compile because cx and cy are const
    swap_v(7.7,9.9);    // compiles but doesn't swap
    double dx = 7.7;
    double dy = 9.9;
    std::cout << "dx / dy = " << dx << " / " << dy << "\n";
    swap_v(dx, dy);
    std::cout << "swap_v dx / dy = " << dx << " / " << dy << "\n";
    // swap_r(dx, dy); // ref of type int (non-const) cannot be init with 'double'
    std::cout << "Testing swap_auto..." << "\n";
    std::cout << "x / y = " << x << " / " << y << "\n";
    swap_auto(x, y);
    std::cout << "(swap_auto(x, y)) x / y = " << x << " / " << y << "\n";
    std::cout << "dx / dy = " << dx << " / " << dy << "\n";
    swap_auto(dx, dy);
    std::cout << "(swap_auto(dx, dy)) dx / dy = " << dx << " / " << dy << "\n";

    return 0;
}
