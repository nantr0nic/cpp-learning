#include <iostream>
#include <vector>
#include <stdexcept>
#include <expected> // this is a new C++23 feature
#include <string>

using std::cin, std::cout, std::cerr, std::vector;

// std::expected<int, std::string>; // this is a new C++23 feature

void error(const std::string& s1, const std::string& s2)
{
    throw std::runtime_error(s1 + s2);
}

int main() {
    try
    {
        vector<int> v;              // a vector of ints
        for (int x; cin >> x;) {
            v.push_back(x);
        }
        for (long unsigned int i = 0; i < v.size(); ++i) {
            cout << "v[" << i << "] == " << v[i] << '\n';
        }
        return 0;
    }
    catch (const std::out_of_range& e)
    {
        cerr << "Oops! Range error: " << e.what() << "\n";
        return 1;
    }
    catch (const std::runtime_error& e)
    {
        cerr << "Exception: something went wrong -> " << e.what() << "\n";
        return 2;
    }
    catch (...)
    {
        cerr << "Unknown exception...\n";
        return 3;
    }
}