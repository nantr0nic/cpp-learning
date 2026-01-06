// Scoping
// Demonstrates scopes

#include <iostream>

using namespace std;

void func();

int main() {
    int var = 5; // local variable in main()
    cout << "In main() var is " << var << "\n\n";

    func();

    cout << "Back in main() var is (still): " << var << "\n\n";

    {
        cout << "In main(), in a new (double) scope var is (still): " << var << "\n\n";

        cout << "But.. now creating new var in the new scope. \n";
        int var = 10000; // variable in new scope, hides other variable named var
        cout << "In main() in this new (double) scope, var is now: " << var << "\n\n";
        {
            int var = 666;
            cout << "Triple scope, in here var is now: " << var << "\n\n";
        }
        cout << "After end of double scope, is the original double scope still 10000?\nLook. Var: " << var << endl;
    }

    cout << "At end of main() var(s) created in new scopes no longer exist.\n";
    cout << "At end of main() var is the original value: " << var << "\n";

    return 0;
}

void func() {
    int var = -12345; // local variable in func()
    cout << "In func() var is: " << var << "\n\n";
}