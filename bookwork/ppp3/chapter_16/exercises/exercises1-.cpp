//$ ----- Chapter 16 Exercises ----- //

#include <cstddef>
#include <cstring>
#include <print>

// #1
void to_lower(char* s)
{
    for (size_t i = 0; i < strlen(s); ++i)
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            s[i] += 32;
        }
}

// #2
char* str_dup(const char* s)
{
    char* copy_ptr{new char[strlen(s)]};
    for (size_t i = 0; i < strlen(s); ++i)
        copy_ptr[i] = s[i];

    return copy_ptr;
}

// #3
// I couldn't get this to work without adding "const" to the return type
const char* find_x(const char* s, const char* x)  // find the first x in s
{
    for (size_t i = 0; i < strlen(s); ++i)
    {
        if (s[i] == *x)
        {
            return &s[i];
        }
    }
    return nullptr;
}

// #4
int str_cmp(const char* s1, const char* s2)
{
    while (*s1 && (*s1 == *s2)) 
    {
        ++s1;
        ++s2;
    }

    if (*s1 < *s2)
        return -1;
    if (*s1 > *s2)
        return 1;
    return 0;
}

int main()
{
    //$ #1
    char s[] = "Hello, World!";
    to_lower(s);
    std::println("{}", s);

    //$ #2
    char* heap = str_dup(s);
    for(size_t i = 0; i < strlen(heap); ++i)
        std::print("{}", heap[i]);

    //$ #3
    const char e3[] = "Antidisestablishmentarianism";
    const char b = 'b';
    const char* b2 = find_x(e3, &b);
    std::println("\n{}", b2);

    //$ #4
    // -1 if first string comes before second alphabetically
    // 0 is they're equal
    // 1 is first string comes after second alphabetically
    const char e3_2[] = "Antidisestablishmentarianism";
    std::println("{}", str_cmp(e3, e3_2));

    //$ #5
    char words[1] = {'b'};
    char* words_ptr = words;

    char* bad1 = str_dup(words_ptr);
    to_lower(bad1);
    std::println("{}", str_cmp(e3, words_ptr));
    std::println("{}", *bad1);


}