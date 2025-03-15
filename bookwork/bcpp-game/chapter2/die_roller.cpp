// Die Roller
// Demonstrates genreating random numbers

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
    srand(static_cast<unsigned int>(time(0))); // seed random number generator

    int randomNumber = rand(); //generate random number

    int die = (randomNumber % 6) + 1; // get a number between 1 and 6
    cout << "You rolled a " << die << endl;
    cout << "Number " << randomNumber << endl;
    cout << "...out of a max of " << RAND_MAX << "\n";

    return 0;
}