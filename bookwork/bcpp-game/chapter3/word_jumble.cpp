// Word Jumble
// The classic word jumble game where the player can ask for a hint

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    enum fields {WORD, HINT, NUM_FIELDS}; // 0, 1, 2 -- last enum is number of elements
    const int NUM_WORDS = 5;
    const string WORDS[NUM_WORDS][NUM_FIELDS] = 
    {
        {"wall", "Do you feel you're banging your head against something?"}, // [0][0], [0][1]
        {"glasses", "These might help you see the answer."}, // [1][0], [1][1]
        {"labored", "Going slowly, is it?"}, // [2][0], [2][1]
        {"persistent", "Keep at it."}, // [3][0], [3][1]
        {"jumble", "It's what the game is all about."}, // [4][0], [4][1]
    };

    srand(static_cast<unsigned int>(time(0))); // seed for rand()
    int choice = (rand() % NUM_WORDS); // will return 0-4
    string theWord = WORDS[choice][WORD]; // word to guess // WORDS[0-4][0] <-- because of enum fields
    string theHint = WORDS[choice][HINT]; // hint for word // WORDS[0-4][1] <-- because of enum fields

    string jumble = theWord; // jumbled version of word
    int length = jumble.size(); // or .length()
    for (int i = 0; i < length; ++i) // do this for the length of the word
    {
        int index1 = (rand() % length); // length for 'hello' is 5, this will return 0-4 thus matching index
        int index2 = (rand() % length); // pick 2 random letters
        char temp = jumble[index1]; // keep track of original letter
        jumble[index1] = jumble[index2]; // make 1st letter the 2nd letter
        jumble[index2] = temp; // make 2nd letter the 1st letter (stored in temp)
    }

    cout << "\t\t\tWelcome to Word Jumble!\n\n";
    cout << "Unscramble the letters to make a word.\n";
    cout << "Enter ’hint’ for a hint.\n";
    cout << "Enter ’quit’ to quit the game.\n\n";
    cout << "The jumble is: " << jumble;

    string guess;
    cout << "\n\nYour guess: ";
    cin >> guess;

    while ((guess != theWord) && (guess != "quit"))
    {
        if (guess == "hint")
        {
            cout << theHint;
        }
        else
        {
            cout << "Sorry, that's not it.";
        }

        cout << "\n\nYour guess: ";
        cin >> guess;
    }
    // the loop is above, getting the word or 'quit' exits the loop and execution continues below
    if (guess == theWord)
    {
        cout << "\nThat's it! You guessed it!\n";
    }

    cout << "\nThanks for playing.\n";

    return 0;
}