// 3 Exercise problems from end of chapter 1

/*
1. Create a list of six legal variable names—three good choices and three
bad choices. Explain why each name falls into the good or bad category.
        Good
    1.1 playerHealth - it is descriptive, under 15 characters, and is camel case.
    1.2 total_score - descriptive, underline sets up other names like round_score
    1.3 (const) DT - uppercase for constant, it is short and common name.
        Bad
    1.4 playerhealthpoints -- too long (>15 chars) and not camel case
    1.5 string_name -- uses a C++ keyword
    1.6 thp -- unclear (total health points)
*/

/*
2. What’s displayed by each line in the following code snippet? Explain
each result.
cout << "Seven divided by three is " << 7 / 3 << endl;
cout << "Seven divided by three is " << 7.0 / 3 << endl;
cout << "Seven divided by three is " << 7.0 / 3.0 << endl;

    2.1) 7 / 3 will show the nearest integer (2) because two integers are being used for the calculation.
    2.2 + 2.3) 7.0 / 3 and 7.0 / 3.0 will both show 2.33333 because at least one number is a float value. 
            It is truncated at 5 decimal points. 
*/

/* 
3. Write a program that gets three game scores from the user and displays
the average. 
*/

#include <iostream>

using std::cout;
using std::cin;
using std::endl;
// can also do "using namespace std;" -- practicing this way though.

int main()
{
    int score_1 = 0;
    int score_2 = 0;
    int score_3 = 0;

    cout << "Let's enter three scores!\n";
    cout << "1. >> " ;
    cin >> score_1;
    //cout << endl; <-- unnecessary.
    cout << "2. >> ";
    cin >> score_2;
    //cout << endl; <-- unnecessary.
    cout << "3. >> ";
    cin >> score_3;
    //cout << endl; <-- unnecessary.
    int score_total = (score_1 + score_2 + score_3);
    int score_avg = (score_total / 3);
    cout << "The average score is: " << score_avg << " points!\n";
}
