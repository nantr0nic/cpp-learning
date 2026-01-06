// initialization

int a = 0;  // Initialized to 0 // explicitly set using a literal
int b{};    // Initialized to 0 // braced initialization <-- always applicable *
int c = {}; // Initialized to 0 // equals braces
int d;      // Initialized to 0 (maybe) // unreliable!

int e = 42;
int f{ 42 };
int g = { 42 };
int h(42);

int main() {
    int array_1[]{ 1, 2, 3 };   // Array of length 3; 1, 2, 3
    int array_2[5]{};           // Array of length 5; 0, 0, 0, 0, 0
    int array_3[5]{ 1, 2, 3 };  // Array length of 5; 1, 2, 3, 0, 0
    int array_4[5];             // Array length 5; uninitialized values
}