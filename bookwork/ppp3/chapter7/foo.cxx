module;
#include <iostream>

export module foo;

int foo = 0;

export void print_foo() { std::cout << foo << "\n"; }
export void set_foo(int x) { foo = x; }
export int get_foo() { return foo; }