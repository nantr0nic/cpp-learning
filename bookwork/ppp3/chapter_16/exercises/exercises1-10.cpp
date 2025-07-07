//$ ----- Chapter 16 Exercises ----- //

#include <cstddef>
#include <cstdlib>
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

// #7 / 9
std::string cat_dot(const char* s1, const char* s2, char p)
{
    std::string s1copy {s1};
    std::string s2copy {s2};
    return s1copy + p + s2copy;
}

// #8 / 9
std::string cat_dot(const std::string& s1, const std::string& s2, char p)
{
    std::string s1copy {s1};
    std::string s2copy {s2};
    return s1copy + p + s2copy;
}

// #10
char* cat_dot_c(const char* s1, const char* s2, const char* p)
{
    size_t s1size = strlen(s1);
    size_t s2size = strlen(s2);
    size_t psize = strlen(p);
    char* res = (char*)malloc(s1size + s2size + psize + 1); // +1 for terminating 0

    if (res == nullptr)
        return nullptr;

    strcpy(res, s1);
    strcpy(res+s1size, p);
    strcpy(res+s1size+psize, s2);
    return res;
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
    // I tried various 'bad' pointers and compiled as release without debug and still
    // didn't notice anything weird.
    // char words[1] = {'b'};
    char* words_ptr = new char;

    char* bad1 = str_dup(words_ptr);
    to_lower(bad1);
    std::println("{}", str_cmp(e3, words_ptr));
    std::println("{}", *bad1);

    //$ #6
    std::println("{}", strcmp(words_ptr, bad1));

    //$ #7
    std::println("{}", cat_dot("John", "Lennon", '@'));

    //$ #10
    char john[] = "John";
    char sep[] = "@";
    char lennon[] = "Lennon";
    char* jl = cat_dot_c(john, lennon, sep);
    std::println("{}", jl);
    delete[] jl;

    char anti[] = "Antidisestablish";
    char sep2[] = "<==>";
    char ment[] = "mentarianism";
    char* am = cat_dot_c(anti, ment, sep2);
    std::println("{}", am);
    delete[] am;

    return 0;
}