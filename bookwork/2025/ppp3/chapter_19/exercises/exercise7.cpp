/*=================================================================*
*                            Exercise 7                            *
*                                                                  *
*Find the lexicographical last string in an unsorted vector<string>*
 *=================================================================*/
import std;

void alpha_last(const std::vector<std::string>& vec)
{
    std::string word = vec[0];
    for (const auto& i : vec)
    {
        if (word < i)
        {
            word = i;
        }
    }

    std::println("The lexicographically last string is: {}", word);
}

int main()
{
    std::vector<std::string> stringVector{"This", "is", "a", "zebra", "sentence", "of", "apples", "zooooo" };

    alpha_last(stringVector);

    return 0;
}