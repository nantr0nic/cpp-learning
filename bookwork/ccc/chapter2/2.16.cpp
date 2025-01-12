#include <cstdio>
#include <cstring>

struct Book {
    char name[256];
    int year;
    int pages;
    bool hardcover;
};

int main() {
    Book neuromancer;
    strcpy(neuromancer.name, "Neuromancer");
    neuromancer.year = 1995;
    neuromancer.pages = 271;
    neuromancer.hardcover = false;
    printf(
        "Book: %s.\nYear: %d\nPages: %d\nHardcover: %d\n", 
    neuromancer.name, neuromancer.year, neuromancer.pages, neuromancer.hardcover
    );
    return 0;
}