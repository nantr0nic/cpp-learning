// Instructions
// Demonstrates writing new functions

#include <iostream>

using namespace std;

/* In Python the function needs to precede where it is called. In CPP 
the 'function prototype' IS a declaration preceding a first call, and
it seems the function body can be after it is called. */

// function prototype (declaration)
void instructions();

int main() {
    instructions();
    return 0;
}

// function definition
void instructions() {
    cout << "Welcome to the most fun you've ever had with text!\n\n";
    cout << "Here's how to play the game... \n";
}
