#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using std::string, std::vector;

string list_numbers(int num, const vector<unsigned long int>& int_vec);
string print_results(int num, const vector<unsigned long int>& int_vec);

int main()
{
    int num = 0; // the N-numbers of the Fibonacci sequence
    unsigned long int first = 1; // relative 'first' number of sequence to add
    unsigned long int second = 1; // relative 'second' number of sequence to add
    unsigned long int temp = 0; // temp holder for shifting around the numbers
    vector<unsigned long int> fib_seq; // vector of Fibonacci numbers

    // Declaring the maximums of various data types
    constexpr short int s_int_max = 32767; // short int max
    constexpr unsigned short int u_s_int_max = 65535; // unsigned short int max
    constexpr int int_max = 2147483647; // signed int's max
    constexpr unsigned int u_int_max = 4294967295; // unsigned int's max
    constexpr long int l_int_max = 9223372036854775807; // long int max (on 64-bit linux system...)
    constexpr unsigned long int u_l_int_max = 18446744073709551615; // unsigned long int max (on 64-bit linux system...)
    // Declaring bool values for whether maxes have been reached
    bool s_int_max_reached = false;
    bool u_s_int_max_reached = false;
    bool int_max_reached = false;
    bool u_int_max_reached = false;
    bool l_int_max_reached = false;
    bool u_l_int_max_reached = false;


    std::cout << "How many numbers of the Fibonacci sequence would you like?\n";
    std::cout << "(This program can only go up to the 93rd number in the sequence)\n >> ";
    std::cin >> num;

    // Add the first two values of the Fibonacci sequence to the vector
    fib_seq.push_back(1);
    fib_seq.push_back(1);

    // Doing the Fib. math and adding the result to the vector
    // Also, checking if data type maximums are reached along the way
    for (int i = 2; i < num; ++i)
    {
        temp = first + second;

        // Check if data type maximums reached
        if (!s_int_max_reached && second >= s_int_max - first)
        {
            std::cout << "Reached 'short int' max at the " << i << "-th number: " << second << "\n";
            s_int_max_reached = true;
        }
        else if (!u_s_int_max_reached && second >= u_s_int_max - first)
        {
            std::cout << "Reached 'unsigned short int' max at the " << i << "-th number: " << second << "\n";
            u_s_int_max_reached = true;
        }
        else if (!int_max_reached && second >= int_max - first)
        {
            std::cout << "Reached 'int' max at the " << i << "-th number: " << second << "\n";
            int_max_reached = true;
        }
        else if (!u_int_max_reached && second >= u_int_max - first)
        {
            std::cout << "Reached 'unsigned int' max at the " << i << "-th number: " << second << "\n";
            u_int_max_reached = true;
        }
        else if (!l_int_max_reached && second >= l_int_max - first)
        {
            std::cout << "Reached 'long int' max at the " << i << "-th number: " << second << "\n";
            l_int_max_reached = true;
        }
        else if (!u_l_int_max_reached && second >= u_l_int_max - first)
        {
            std::cout << "Reached 'unsigned long int' max at the " << i << "-th number: " << second << "\n";
            u_l_int_max_reached = true;
        }

        first = second;
        second = temp;
        fib_seq.push_back(second);  // add the number of the Fib. sequence to the vector after math
    }

    // Print the results!
    print_results(num, fib_seq);
    return 0;
}

string list_numbers(int num, const vector<unsigned long int>& int_vec)
// This lists the numbers contained in the vector
// Necessary because of << operator being unfriendly with vectors
{
    std::ostringstream oss;
    for (int i = 0; i < num; ++i)
    {
        oss << " " << int_vec[i];
    }
    return oss.str();
}

string print_results(int num, const vector<unsigned long int>& int_vec)
// This prints the final results
{
    std::cout << "The first " << num << " numbers of the Fibonacci sequence are...\n";
    std::cout << list_numbers(num, int_vec) << std::endl;
    return "Done!\n";
}