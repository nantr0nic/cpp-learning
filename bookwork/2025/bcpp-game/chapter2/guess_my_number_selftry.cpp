// Guess My Number
// Tried exercise without looking at author's code.
// Too many lines.

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(static_cast<unsigned int>(time(0))); // seed random number generator

    cout << "\tWelcome to Guess My Number\n";

    int randomNumber = rand();
    int goalNumber = (randomNumber % 100) + 1;
    int guess;
    int success = 0;
    int guessCount = 0;

    while (!success)
    {
        cout << "Enter a guess: ";
        cin >> guess;

        guessCount += 1;

        if (guess == goalNumber)
        {
            cout << "That's it! You got it in " << guessCount << " guesses!" << endl;
            success = 1;
        }
        else if (guess > goalNumber)
        { 
            cout << "Too high!\n";
        }
        else if (guess < goalNumber)
        {
            cout << "Too low!\n";
        }
        else
        {
            cout << "That's not a valid guess. Try again.\n";
        }
    }

    return 0;
}