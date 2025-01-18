/********************************************************************** 
* 2. Rewrite the Hangman game from Chapter 4, “The Standard Template
*    Library: Hangman,” using functions. Include a function to get the
*    player’s guess and another function to determine whether the player’s
*    guess is in the secret word.
***********************************************************************/

// Hangman
// The classic game of hangman

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cctype>
#include <random>

using namespace std;

int main()
{
    // Setup //
    char userGuess();
    void gameInfo(int MAX_WRONG, int wrong, string used, string soFar);

    const int MAX_WRONG = 8; // max number of incorrect guesses
    // Make collection of possible words to guess
    vector<string> words;
    words.push_back("GUESS");
    words.push_back("HANGMAN");
    words.push_back("DIFFICULT");
    // Create random device for shuffle
    random_device rd;
    mt19937 g(rd());
    // Use the above random device to shuffle words
    shuffle(words.begin(), words.end(), g);

    const string THE_WORD = words[0]; // After shuffle, make 1st word THE_WORD
    int wrong = 0; // initialize wrong guesses to 0
    string soFar(THE_WORD.size(), '-'); // initialize soFar to -'s for length of word
    string used = ""; // empty string of letters already guessed

    cout << "Welcome to Hangman. Good luck!\n";

    // Main loop
    while ((wrong < MAX_WRONG) && (soFar != THE_WORD)) 
    {
        gameInfo(MAX_WRONG, wrong, used, soFar);

        char guess = userGuess();

        // find() the guess in used and if it is not equal to 'null' then it exists, therefore...
        while (used.find(guess) != string::npos)
        {
            cout << "\nYou've already guessed " << guess << endl;
            cout << "Enter your guess: ";
            cin >> guess;
            guess = toupper(guess);
        }

        used += guess;

        if (THE_WORD.find(guess) != string::npos)
        {
            cout << "That's right! " << guess << " is in the word.\n";
            // Update soFar to include newly guessed letter
            for (int i = 0; i < THE_WORD.length(); ++i)
            {
                if (THE_WORD[i] == guess)
                {
                    soFar[i] = guess;
                }
            }
        }

        else
        { 
            cout << "Sorry, " << guess << " isn't in the word.\n";
            ++wrong;
        }

        // Shut down

        if (wrong == MAX_WRONG)
        {
            cout << "\nYou've been hanged!";
        }
        else 
        {
            cout << "\nYou guessed it!";
        }
    }

    cout << "\nThe word was " << THE_WORD << endl;

    return 0;
}

char userGuess() {
    char guess; // char cuz single letter
    cout << "\n\nEnter your guess: ";
    cin >> guess;
    guess = toupper(guess); // make uppercase since secret word is uppercase
    return guess;
}

void gameInfo(int MAX_WRONG, int wrong, string used, string soFar) {
    cout << "\n\nYou have " << (MAX_WRONG - wrong);
    cout << " incorrect guesses left.\n";
    cout << "\nYou've used the following letters:\n" << used << endl;
    cout << "\nSo far, the word is:\n" << soFar << endl;
}