// Exploring output operator <<

#include <iostream>

using namespace std;

int main()
{
    cout << "Let's explore some basic output operator patterns! (And escape sequences lol)" << endl;
    cout << "First... a simple cout and \\n. \n";
    cout << "This line is \"cout << \"string\" << endl;\"" << endl;
    cout << "Second kind happening NOW.";
    cout << endl;
    cout << "Now, two endl's after this string.";
    cout << endl;
    cout << endl;
    cout << "Now, two \"cout << \\n\"";
    cout << "\n";
    cout << "\n";
    cout << "Now, lets try a series of operators, strings, and endl's next.\n";
    cout << "String 1." << endl << "String 2." << endl << "String 3." << endl;
    cout << "That was 3 endl's on one line! THIS line ends in a \\n.\n";
    cout << "Lets try the same thing but using \\n's instead of endls. Should be identical?\n";
    cout << "String 1." << "\n" << "String 2." << "\n" << "String 3." << "\n";
    cout << "I think that's it. For now.";
    cout << "Wait, no... for funsies let's try \"cout << \"\\n\\n\\n\"\" (Would ya look at THOSE escapes?)\n";
    cout << "\n\n\n";
    cout << "How about three endl's?\n";
    cout << endl << endl << endl;
    cout << "That was \"cout << endl << endl << endl;\"\n";
    cout << "Now, I'm done. Really :)\n";
    return 0;
}