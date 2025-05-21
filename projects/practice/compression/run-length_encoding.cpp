#include <iostream>
#include <string>

std::string compressRLE(const std::string& input)
{
    std::string compressed {};

    for (size_t i {0}; i < input.length(); )
    {
        char currentChar {input[i]};
        size_t count {1};

        // Count consecutive repeated characters
        while ((i + count < input.length()) && (input[i + count] == currentChar))
        {
            ++count;
        }

        compressed += currentChar;
        compressed += std::to_string(count);

        i += count;
    }

    return compressed;
}

int main()
{
    std::string text {"cccoooooommmprrreeeesssssssssSSSSSSSSSeeeeeeeeeeeedddddddddddddddddddddd"};
    std::cout << "Original: " << text << '\n';

    std::string compressedText {compressRLE(text)};
    std::cout << "Compressed: " << compressedText << '\n';

    std::cout << '\n';

    std::string text2 {"This is sentence demonstrates that RLE is NOT good for natural language."};
    std::cout << "Original: " << text2 << '\n';

    std::string compressedText2 {compressRLE(text2)};
    std::cout << "Compressed: " << compressedText2 << '\n';

    return 0;
}