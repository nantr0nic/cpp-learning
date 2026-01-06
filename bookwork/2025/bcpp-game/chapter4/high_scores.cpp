// High Scores
// Demonstrates algorithms, vectors, new shuffle

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>

using namespace std;

int main()
{
    vector<int>::const_iterator iter;

    cout << "Creating a list of scores.";
    vector<int> scores;
    scores.push_back(1500);
    scores.push_back(3500);
    scores.push_back(7500);

    cout << "\nHigh Scores:\n";

    for (iter = scores.begin(); iter != scores.end(); ++iter)
    {
        cout << *iter << endl;
    }

    cout << "\nFinding a score.";
    int score;
    cout << "\nEnter a score to find: ";
    cin >> score;
    iter = find(scores.begin(), scores.end(), score);
    if (iter != scores.end())
    {
        cout << "Score found.\n";
    }
    else
    {
        cout << "Score not found.\n";
    }

    cout << "\nRandomizing scores.";
    /* The book suggests using random_shuffle() but that is deprecated and removed
    from C++14 and higher. Perplexity says the new method is to use "shuffle" which
    is based off the new/superior random library, rather than rand(). 
    Here is what the book suggested:
    srand(static_cast<unsigned int>(time(0)));
    random_shuffle(scores.begin(), scores.end());
    */
    // Here is the new suggested method:
    // Create a random number generator
    std::random_device rd;
    std::mt19937 g(rd());
    // Use std::shuffle                       vvv third argument is the RNG
    std::shuffle(scores.begin(), scores.end(), g);
    cout << "\nHigh Scores:\n";
    for (iter = scores.begin(); iter != scores.end(); ++iter)
    {
        cout << *iter << endl;
    }

    cout << "\nSorting scores.";
    sort(scores.begin(), scores.end());
    cout << "\nHigh Scores:\n";
    for (iter = scores.begin(); iter != scores.end(); ++iter)
    {
        cout << *iter << endl;
    }
    
    // Trying out capacity() and reserve() below.

    cout << "\nBefore leaving, let's check out capacity().\n";
    cout << "Capacity of <scores> is: " << scores.capacity() << endl;
    cout << "Let's add some elements.\n";
    int j = 0;
    while (j < 10)
    {
        scores.push_back(j);
        ++j;
    }
    cout << "Current scores:\n";
    for (iter = scores.begin(); iter != scores.end(); ++iter)
    {
        cout << *iter << endl;
    }
    cout << "Capacity of <scores> NOW is: " << scores.capacity() << endl;
    cout << "Let's reserve.. 40 for <scores>.\n";
    scores.reserve(40);
    cout << "Capacity of <scores> NOW is: " << scores.capacity() << endl;
    cout << "Add another 10 to <scores.\n";
    for (int i; i < 10; ++i)
    {
        scores.push_back(i * 125);
    }
    cout << "Current scores:\n";
    for (iter = scores.begin(); iter != scores.end(); ++iter)
    {
        cout << *iter << endl;
    }
    cout << "Capacity of <scores> NOW is... " << scores.capacity() << endl;


    return 0;
}