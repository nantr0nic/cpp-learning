// Character types

#include <cstdio>

int main() {
    char x = 'M';
    wchar_t y = L'Z';
    printf("Windows binaries start with %c%lc.\n", x, y);
}

/*
char --> The default type, always 1 byte. May or may not be signed. (Example: ASCII.)
char16_t --> Used for 2-byte character sets. (Example: UTF-16.)
char32_t --> Used for 4-byte character sets. (Example: UTF-32.)
signed char --> Same as char but guaranteed to be signed.
unsigned char --> Same as char but guaranteed to be unsigned.
wchar_t --> Large enough to contain the largest character of the implementation’s locale. (Example: Unicode.)
*/