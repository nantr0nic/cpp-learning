#include <iostream>

using std::cout;

int main()
{
    constexpr double number {1234567.89};

    cout << "defaultfloat: " << std::defaultfloat << number << "\n";
    cout << "fixed: " << std::fixed << number << "\n";
    cout << "scientific: " << std::scientific << number << "\n";

    /*
    Explain: "Which ouput form presents the user with the most accurate representation?
            Explain why."

        I think the 'most accurate' representation depends upon the needs of the user. 
    For financial data, the defaultfloat and scientific is useless. For those users, I think
    the most accurate representation would be to the thousandths place. For a physicist,
    the 6-point precision would be preferable.
    */
    return 0;
}
