// Pointing
// Demonstrates using pointers

#include <iostream>
#include <string>

using namespace std;

int main() {
    int* pAPointer;     // declare a pointer
    int* pScore = 0;    // declare and initialize a pointer
    int score = 1000;
    pScore = &score;    // assign pointer pScore address of variable score

    cout << "Assigning &score to pScore\n";
    cout << "&score is: " << &score << "\n";        // address of score variable
    cout << "pScore is: " << pScore << "\n";        // address stored in pointer.
    cout << "*pScore is: " << *pScore << "\n\n";    // value pointed to by pointer.

    cout << "Adding 500 to score\n";
    score += 500;
    cout << "score is: " << score << "\n";
    cout << "*pScore is: " << *pScore << "\n\n";

    cout << "Adding 500 to *pScore\n";
    *pScore += 500;
    cout << "score is : " << score << "\n";
    cout << "*pScore is: " << *pScore << "\n\n";

    cout << "Assigning &newScore to pScore\n";
    int newScore = 5000;
    pScore = &newScore;
    cout << "&newScore is: " << &newScore << "\n";
    cout << "pScore is: " << pScore << "\n";
    cout << "newScore is: " << newScore << "\n";
    cout << "*pScore is: " << *pScore << "\n\n";

    cout << "Assigning &str to pStr\n";
    string str = "score";
    string* pStr = &str;        // pointer to string object

    cout << "str is: " << str << "\n";
    cout << "*pStr is: " << *pStr << "\n";
    cout << "(*pStr).size() is: " << (*pStr).size() << "\n";
    cout << "pStr->size() is: " << pStr->size() << "\n";
    cout << "Address of pStr is: " << pStr << "\n\n";

    string test = "test";
    string* const pTesting = &test;     // a CONSTANT POINTER 
    // pointer cannot be reassigned but it can still change the thing its pointing to
    cout << "Does this work?\nAddress of 'test' is: " << &test << "\n";
    cout << "Address of const pTesting ITSELF is: " << &pTesting << "\n";
    cout << "But pTesting itself POINTS to: " << pTesting << "\n";
    *pTesting = "test is changed?";
    cout << *pTesting << "\n\n";

    string test2 = "test2";
    const string* pTest2 = &test2;      // a POINTER TO A CONSTANT
    // pointer CANNOT change what its pointing to BUT it CAN be reassigned to a diff obj/value
    cout << "test2 : " << test2 << "\n";
    cout << "pTest2: " << *pTest2 << "\n";
    cout << "test2 address: " << &test2 << "\n";
    cout << "pTest2 address: " << pTest2 << "\n\n";

    string test3 = "test3";
    const string* const pTest3 = &test3; // a constant pointer to a constant...
    // cannot change what its pointing to NOR be reassigned.
    cout << *pTest3 << "\n";
    // doesn't have to point to a constant (but it can) so...
    test3 = "test3 has changed";
    cout << *pTest3 << "\n";

    ////////
    int i = 1;
    int* const p = &i;          // a constant pointer (1)
    const int* p = &i;          // a pointer to a constant (2)
    const int* const p = &i;    // a constant pointer to a constant (3)
    /*
    1) Can only point to the object to which it was initialized to point.
        the memory address stored in the pointer itself is constant and cannot change.
        A constant pointer can only point to a non-constant value;
        it CANNOT point to a constant.
    2) Cannot be used to change the value to which it points. CAN point to different
        objects during the life of a program. A pointer to a constant can point to a 
        constant OR non-constant value.
    3) Can only point to the value to which it was initialized to point -- AND it CANNOT
        be used to change the value to which it points. It can be initialized to point
        to a constant OR non-constant value.*/

    

    return 0;
}