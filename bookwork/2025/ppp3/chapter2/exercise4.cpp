#include <iostream>
using namespace std;

int main()
{
    double val1 = 0;
    double val2 = 0;
    cout << "Enter first value: ";
    cin >> val1;
    cout << "\nEnter second value: ";
    cin >> val2;
    if (val1 < val2)
        cout << val1 << " is smaller than " << val2 << "\n";
    if (val1 > val2)
        cout << val1 << " is greater than " << val2 << "\n";
    cout << "Sum: " << val1 + val2 << "\n";
    cout << "Difference: " << val1 - val2 << "\n";
    cout << "Product: " << val1 * val2 << "\n";
    cout << "Ratio: " << val1 / val2 << endl;
    return 0;
}