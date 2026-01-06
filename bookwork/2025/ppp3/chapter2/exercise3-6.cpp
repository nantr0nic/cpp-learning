/*
Write a program that prompts the user to enter three integer values, and
then outputs the values in numerical sequence separated by commas. So,
if the user enters the values 10 4 6, the output should be 4, 6, 10. If two
values are the same, they should just be ordered together. So, the input 4
5 4 should give 4, 4, 5.
*/

//////// First way... ////////
/*
#include <iostream>

int main()
{
    int a{0}, b{0}, c{0}, temp{0};
    std::cout << "Enter three integer values\n(a) >> ";
    std::cin >> a;
    std::cout << "(b) >> ";
    std::cin >> b;
    std::cout << "(c) >> ";
    std::cin >> c;

    if (a > b)
    {
        temp = a;
        a = b;
        b = temp;
    }
    if (a > c)
    {
        temp = a;
        a = c;
        c = temp;
    }
    if (b > c)
    {
        temp = b;
        b = c;
        c = temp;
    }

    std::cout << a << ", " << b << ", " << c;
    return 0;
}
*/

/////////// Second way using arrays and std::sort /////////////
/*
#include <iostream>
#include <algorithm>

using std::cin, std::cout;

int main()
{
    int numbers[3] = {0, 0, 0};
    cout << "Enter three integer values\n(a) >> ";
    cin >> numbers[0];
    cout << "(b) >> ";
    cin >> numbers[1];
    cout << "(c) >> ";
    cin >> numbers[2];

    std::sort(numbers, numbers + 3);

    cout << numbers[0] << ", " << numbers[1] << ", " << numbers[2] << std::endl;
    return 0;
}
*/

///////// Third way using vectors and std::sort ///////////
#include <iostream>
#include <algorithm>
#include <vector>

using std::cin, std::cout;

int main()
{
    std::vector<int> numbers(3, 0);
    cout << "Enter three integer values\n(a) >> ";
    cin >> numbers[0];
    cout << "(b) >> ";
    cin >> numbers[1];
    cout << "(c) >> ";
    cin >> numbers[2];

    std::sort(numbers.begin(), numbers.end());

    cout << numbers[0] << ", " << numbers[1] << ", " << numbers[2] << std::endl;
    return 0;
}

