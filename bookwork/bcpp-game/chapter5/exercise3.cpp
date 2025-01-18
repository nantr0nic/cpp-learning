/*
3. Using default arguments, write a function that asks the user for a number
and returns that number. The function should accept a string prompt from
the calling code. If the caller doesn’t supply a string for the prompt, the
function should use a generic prompt. Next, using function overloading,
write a function that achieves the same results.
*/

#include <iostream>

using namespace std;

int number1(int num, string question = "Enter a number: ");
string number1(string question = "Enter a number string: ");

int main() {
    cout << number1() << "\n";                              // calls string number1()
    cout << number1("Please enter a number: ") << "\n";     // calls string number1()
    cout << number1(5) << "\n";                             // calls int number1()
    cout << number1(6, "Pweeze enter a number: ") << "\n";  // calls int number1()

    // The code calls either int or string number1() based on the arguments passed
    return 0;
}

int number1(int num, string question) {
    cout << question;
    cin >> num;
    return num;
}

string number1(string question) {
    string num;
    cout << question;
    cin >> num;
    return num;
}