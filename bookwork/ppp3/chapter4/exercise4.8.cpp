#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using std::cin, std::cout, std::vector, std::string;

string list_numbers(int num, const vector<int>& input_integers)
{
    std::ostringstream oss;
    for (int i = 0; i < num; ++i)
    {
        oss << " " << input_integers[i] << " ";
    }
    return oss.str();
}

int main()
{
    short unsigned int sum_num = 0;
    vector<int> input_integers;
    double final_sum = 0;

    cout << "Please enter the number of values you want to sum: ";
    cin >> sum_num;
    cout << "Please enter some integers (press '|' to stop): ";

    for (int x = 0; cin >> x;)
    {
        input_integers.push_back(x);
    }

    for (int i = 0; i < sum_num; ++i)
    {
        final_sum += input_integers[i];
    }

    cout << "The sum of the first " << sum_num << " numbers (" << list_numbers(sum_num, input_integers) << ") is " << final_sum;
    return 0;
}
