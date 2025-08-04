/*===============================================================================*
*                                 Try This p.850                                 *
*                                                                                *
*   What does that list of differences mean in real code? For each of char[],    *
*vector<char>, list<char>, and string, define one with the value "Hello", pass it*
*    to a function as an argument, write out the number of characters in the     *
*  string passed, try to compare it to "Hello" in that function (to see if you   *
*   really did pass "Hello"), and compare the argument to "Howdy" to see which   *
*   would come first in a dictionary. Copy the argument into another variable    *
*                               of the same type.                                *
 *===============================================================================*/
 import std;

template<typename T>
void print(const T& element)
{
    int count = 0;
    for (const auto& e : element)
    {
        std::cout << e;
        ++count;
    }
    std::println("\nPrinted {} characters", count);
}

template<typename T>
void compare(const T& one, const T& two)
{
    if (one < two)
    {
        std::println("{} comes before {}", one, two);
    }
    else
    {
        std::println("{} comes before {}", two, one);
    }
}

template<typename T>
void report_size(const T& element)
{
    std::println("{} is size: {} bytes", element, sizeof(element));
}

 int main()
 {
    const char char_string[] = "Hello";
    const std::vector<char> vec_string{'H', 'e', 'l', 'l', 'o'};
    const std::list<char> list_string{'H', 'e', 'l', 'l', 'o'};
    const std::string string_string = "Hello";

    const char char_string2[] = "Howdy" ;
    const std::vector<char> vec_string2{'H', 'o', 'w', 'd', 'y'};
    const std::list<char> list_string2{'H', 'o', 'w', 'd', 'y'};
    const std::string string_string2{ "Howdy" };

    // char_string will report 6 characters (6th is terminating block '\0')
    print(char_string);
    print(vec_string);
    print(list_string);
    print(string_string);

    std::println("=========================");

    // With the template above, comparing char will actually compare memory addresses
    compare(char_string, char_string2);
    compare(vec_string, vec_string2);
    compare(list_string, list_string2);
    compare(string_string, string_string2);

    std::println("=========================");

    report_size(char_string);
    report_size(vec_string);
    report_size(list_string);
    report_size(string_string);

    std::println("=========================");

    std::println("vector iterator size: {} bytes", sizeof(vec_string.begin()));
    std::println("list iterator size: {} bytes", sizeof(list_string.begin()));
    std::println("string iterator size: {} bytes", sizeof(string_string.begin()));

    std::println("=========================");

    std::println("vector element size: {} bytes", sizeof(*vec_string.begin()));
    std::println("list element size: {} bytes", sizeof(*list_string.begin()));
    std::println("string element size: {} bytes", sizeof(*string_string.begin()));

    std::println("=========================");

    const std::string long_string_string{ "This is a really long string, hopefully long enough to avoid SSO and also long enough to demonstrate some kind of significant difference in size between vectors and lists ...and possibly std::string. I guess we will see. I am not sure how long this needs to be so even though I think we are well beyond the number of characters we need to see a difference I will keep going and keep writing and keep entering sequences of characters demarcated by whitespaces thus signifying individual words :) Okay, I think that should be enough!" };
    std::vector<char> long_vec_string;
    std::list<char> long_list_string;

    for (const char& c : long_string_string)
    {
        long_vec_string.push_back(c);
        long_list_string.push_back(c);
    }

    std::println("For the following lines, vector/list/string refer to the very very long string: {}", long_string_string);
    std::println("\n");
    std::println("=== Stack Usage (container objects) ===");
    std::println("vector: {} bytes", sizeof(long_vec_string));
    std::println("list: {} bytes", sizeof(long_list_string));  
    std::println("string: {} bytes", sizeof(long_string_string));
    
    std::println("\n=== Heap Usage (estimated) ===");
    std::println("vector: {} bytes", long_vec_string.capacity() * sizeof(char));
    
    // List nodes contain data + 2 pointers
    auto node_size{sizeof(char) + 2 * sizeof(void*)};
    std::println("list: ~{} bytes", long_list_string.size() * node_size);
    
    std::println("string: {} bytes", long_string_string.capacity() * sizeof(char));
    return 0;
 }