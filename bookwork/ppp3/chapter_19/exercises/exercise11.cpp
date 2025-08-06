import std;

/*=========================================================================*
*                               Exercise 11                                *
*                                                                          *
*Given a list<int> as a (by-reference) parameter, make a vector<double> and*
* copy the elements of the list into it. Verify that the copy was complete *
*and correct. Then print the elements sorted in order of increasing value. *
 *=========================================================================*/

std::vector<double> list_to_vec(std::list<int> list)
{
    std::vector<double> temp;
    for (const int& e : list)
    {
        temp.push_back(e);
    }
    return temp;
}

template<typename T>
void sort(std::vector<T>& vec)
{
    for (std::size_t i = 0; i < vec.size(); ++i)
    {
        for (std::size_t j = 0; j < vec.size(); ++j)
        {
            if (vec[j] > vec[i])
            {
                T temp = vec[j];
                vec[j] = vec[i];
                vec[i] = temp;
            }
        }
    }
}

template<typename T>
void bubble_sort(std::vector<T>& vec)
{
    for (std::size_t i{0}; i < vec.size(); ++i)
    {
        for (std::size_t j{0}; j < vec.size() - 1 - i; ++j)
        {
            if (vec[j] > vec[j + 1])
            {
                std::swap(vec[j], vec[j + 1]);  // More efficient than manual swap
            }
        }
    }
}

int main()
{
    const std::list<int> int_list{ 99, 32, 73, 18, 9, 123, 8, 23, 11, 599, 1, 932, 3, 1, };

    std::vector<double> int_vec{ list_to_vec(int_list) };

    std::println("New vec: {}", int_vec);

    // std::sort(int_vec.begin(), int_vec.end());
    bubble_sort(int_vec);

    std::println("New vec: {}", int_vec);

    return 0;
}