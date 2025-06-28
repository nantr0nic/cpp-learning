#include <iostream>
#include <vector>

void sizes(char ch, int i, int* p, double d, double* pd, std::string s, std::string* ps, bool b, bool* pb)
{
    std::cout << "the size of char is " << sizeof(char) << ' ' << sizeof(ch) << '\n';
    std::cout << "the size of int is " << sizeof(int) << ' ' << sizeof(i) << '\n';
    std::cout << "the size of int* is " << sizeof(int*) << ' ' << sizeof(p) << '\n';
    std::cout << "the size of double is " << sizeof(double) << ' ' << sizeof(d) << '\n';
    std::cout << "the side of double* is " << sizeof(double*) << ' ' << sizeof(pd) << '\n';
    std::cout << "the size of string is " << sizeof(std::string) << ' ' << sizeof(s) << '\n';
    std::cout << "the size of string* is " << sizeof(std::string*) << ' ' << sizeof(ps) << '\n';
    std::cout << "the size of bool is " << sizeof(bool) << ' ' << sizeof(b) << '\n';
    std::cout << "the size of bool* is " << sizeof(bool*) << ' ' << sizeof(pb) << '\n';
}

void demonstrate_reference_vs_pointer()
{
    int value{42};
    int& ref{value};
    int* ptr{&value};
    
    std::cout << "sizeof(value): " << sizeof(value) << '\n';    // 4 bytes
    std::cout << "sizeof(ref): " << sizeof(ref) << '\n';        // 4 bytes (same as value!)
    std::cout << "sizeof(ptr): " << sizeof(ptr) << '\n';        // 8 bytes (pointer size)
    std::cout << "sizeof(*ptr): " << sizeof(*ptr) << '\n';      // 4 bytes (dereferenced)
}

void compare_passing_methods()
{
    std::string large_string{"This is a potentially large string that demonstrates the difference"};
    
    // This creates a copy (expensive for large objects)
    auto pass_by_value = [](std::string s) 
    {
        std::cout << "By value - sizeof(s): " << sizeof(s) << '\n';
        return s.length();
    };
    
    // This passes only a reference (cheap)
    auto pass_by_reference = [](const std::string& s) 
    {
        std::cout << "By reference - sizeof(s): " << sizeof(s) << '\n';  // Same size!
        return s.length();
    };
    
    pass_by_value(large_string);      // Expensive copy
    pass_by_reference(large_string);  // Cheap reference
}

int main()
{
    std::vector<double> age {0.33, 22.0, 27.2, 54.2};
    std::vector<int> v1000(1000);
    std::vector<int> v5(5);
    std::vector<int> v9999(9999);

    int x { 17 };
    int* pi = &x;
    int** ppi = &pi;

    char a = 'A';

    double e = 2.71828;
    double* pd = &e;

    std::string s = "This is a string";
    std::string* ps = &s;

    bool b {true};
    bool* pb = &b;

    std::cout << "pi == " << pi << "; contents of pi == " << *pi << "\n";
    std::cout << "ppi == " << ppi << "; contents of ppi == " << *ppi << "\n";
    std::cout << "pd == " << pd << "; contents of pd == " << *pd << "\n";

    std::cout << "size of vector with 4 double elements is: " << sizeof(age) << "\n";
    std::cout << "size of vector with 5 int elements is: " << sizeof(v5) << "\n";
    std::cout << "size of vector with 1000 int elements is: " << sizeof(v1000) << "\n";
    std::cout << "size of vector with 99999 int elements is: " << sizeof(v9999) << "\n";
    std::cout << "Looks like sizeof() doesn't include the space taken up by the contents of the vector!\n";

    sizes(a, x, pi, e, pd, s, ps, b, pb);
    demonstrate_reference_vs_pointer();
    compare_passing_methods();

}