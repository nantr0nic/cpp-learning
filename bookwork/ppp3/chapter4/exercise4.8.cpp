#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>

using std::cin, std::cout, std::cerr, std::vector, std::string;

string list_numbers(int num, const vector<int>& input_integers)
{
    std::ostringstream oss;
    for (int i = 0; i < num; ++i)
    {
        oss << " " << input_integers[i];
    }
    return oss.str();
}

int main()
{
    try
    {
        short unsigned int sum_num = 0;            // [n]umber of integers to add up
        vector<int> input_integers;                // the list of integers
        int final_sum = 0;                      // the sum of the first [n] integers

        cout << "Please enter the number of values you want to sum: ";
        cin >> sum_num;
        cout << "Please enter some integers (press '|' to stop): ";

        for (int x = 0; cin >> x;)
        {
            input_integers.push_back(x);            // put integers to the int vector
        }

        // Check for faulty inputs
        if (input_integers.empty())                 // If user doesn't enter any integers.
        {
            throw std::runtime_error("No integers entered!\n");
        }
        if (sum_num > input_integers.size())    // If [n]umber to sum is greater than entered integers
        {
            throw std::runtime_error("Can't add more numbers than you entered!\n");
        }

        for (int i = 0; i < sum_num; ++i)
        {   // First check if its within the bounds of 'int' data type
            if ((final_sum > 0 && input_integers[i] > 2147483647 - final_sum) ||
                (final_sum < 0 && input_integers[i] < -2147483648 - final_sum))
            {
                throw std::runtime_error("That's more than a poor 'int' can handle :(\n");
            }

            final_sum += input_integers[i];         // add up the [n] integers
        }

        // Print the results
        cout << "The sum of the first " << sum_num << " numbers (";
        cout << list_numbers(sum_num, input_integers) << " ) is " << final_sum;
        return 0;
    }
    catch (const std::runtime_error& e)
    {
        cerr << "Runtime error: " << e.what() << "\n";
        return 1;
    }
    catch (const std::exception& e)
    {
        cerr << "Unexpected error: "<< e.what() << "\n";
        return 2;
    }
    catch (...)
    {
        cerr << "Unknown exception.\n";
        return 2;
    }
}
