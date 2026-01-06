// Exercises at the end of chapter 2

/* Exercise 1:
#include <iostream>

using namespace std;

int main() {
    enum difficulty {EASY=1, NORMAL, HARD};
    difficulty myDifficulty;

    cout << "Difficulty Levels\n\n";
    cout << "1 - Easy\n";
    cout << "2 - Normal\n";
    cout << "3 - Hard\n\n";

    int choice; 
    cout << "Choice: ";
    cin >> choice;

    switch (choice)
    {
        case (EASY):
            cout << "You chose Easy.\n";
            break;
        case (NORMAL):
            cout << "You chose Normal.\n";
            break;
        case (HARD):
            cout << "You chose Hard.\n";
            break;
        default:
        cout << "Invalid choice.\n";
    }
    return 0;
}
*/

/* 
Exercise 2:
    The problem with the loop is that because x is 0 the while loop will never execute. 
*/
    
// Exercise 3:

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(static_cast<unsigned int>(time(0)));

    int secretNumber = 0;
    int tries = 0;
    int guess;

    cout << "\tGuess YOUR Number Game!\nWhere the computer guesses.\n\n";
    cout << "Pick a number between 1-100 for the computer to guess >> ";
    cin >> secretNumber;

    while (guess != secretNumber)
    {
        ++tries;
        guess = ((rand() % 100) + 1);
        if (guess > secretNumber)
        {
            cout << "Computer: " << guess << "\n";
            cout << "Too high!\n";
        }
        else if (guess < secretNumber)
        {
            cout << "Computer: " << guess << "\n";
            cout << "Too low!\n";
        }
        else
        {
            cout << "Computer: " << guess << "\n";
            cout << "The computer got it! It only took " << tries << " guesses." << endl;
        }
    }
    return 0;
}

