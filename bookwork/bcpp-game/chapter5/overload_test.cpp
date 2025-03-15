/*
3. Using default arguments, write a function that asks the user for a number
and returns that number. The function should accept a string prompt from
the calling code. If the caller doesn’t supply a string for the prompt, the
function should use a generic prompt. Next, using function overloading,
write a function that achieves the same results.
*/

#include <iostream>

using namespace std;

int number1(int num, string question = "This is a question.");
int number1(int num, string answer = "This is an answer.");

int main() {
    number1(6, "