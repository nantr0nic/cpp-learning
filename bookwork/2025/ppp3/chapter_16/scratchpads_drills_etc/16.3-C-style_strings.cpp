//$ ------ 16.3 C-style strings ----- //
/*
 * Since early days of C, "a character string has been represented in memory as a
 *      zero-terminated array of characters and accessed through pointers."
*/

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

void char_star()
{
    const char* s = "Danger!";
    // "Our literal strings are C-style strings. Characters of a literal string are const."
    // If we want to change characters, need to use an array:

    char s2[] = "Modifiable";           // 10 chars
    std::cout << "modifiable: " << s2;  // writes "Modifiable"

    s2[6] = 'e';
    s2[7] = 'd';
    s2[8] = 0;                          //$ terminating zero

    std::cout << "modifiable: " << s2;  // writes "Modified"

    // To get the number of characters in a c-style string use strlen() (need <cstring>)
    std::cout << strlen(s2);            // writes 8 (doesn't count terminating 0')
}

// Comparing concatenation between C-style strings and C++ strings

std::string cat(const std::string& name, const std::string& addr)
{
    return name + '@' + addr;
}

char* cat2(const char* name, const char* addr)
{
    size_t nsz = strlen(name);             // name size
    int sz = nsz + strlen(addr) + 2;    // size - +2 for '@' and the terminating zero
    char* res = (char*)malloc(sz);      // using the old allocation function
    strcpy(res, name);                  // copy from *name to *res until a zero is seen
    res[nsz+1] = '@';
    strcpy(res+2, addr);
    return res;
}