#include <algorithm>
#include <iterator>
import std;

template<std::forward_iterator Iter>
Iter copy(Iter start, Iter end, Iter loc)
{
    for (; start != end; ++start)
    {
        *loc = *start;
        ++loc;
    }
    return loc;
}


int main()
{
    // in addition to the drills I'm trying out some new(ish) C++ features 
    // such as uses of auto and deduced types, etc.
    auto int_array = new int[10]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::vector int_vec{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    std::list int_list{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    auto int_array_copy{ int_array };
    std::vector int_vec_copy{ int_vec };
    std::list int_list_copy{ int_list };

    std::println("int_vec is: {}\nint_list is: {}", int_vec, int_list);
    for (int i = 0; i < 10; ++i)
    {
        std::print("int_array[{}] is: {} // ", i, int_array[i]);
        std::println("int_array_copy[{}] is: {}", i, int_array_copy[i]);
    }
    std::println("int_vec_copy is: {}\nint_list_copy is: {}", int_vec_copy, int_list_copy);

    std::println("\nAdding 2 to int_array elements.");
    for (int i = 0; i < 10; ++i)
    {
        int_array[i] += 2;
    }
    for (int i = 0; i < 10; ++i)
    {
        std::println("int_array[{}] is: {}", i, int_array[i]);
    }
    std::println("Adding 3 and 5 to elements of the vector and list, respectively.");
    for (auto& e : int_vec)
    {
        e += 3;
    }

    for (auto& e : int_list)
    {
        e += 5;
    }
    std::println("int_vec is: {}\nint_list is: {}", int_vec, int_list);

    copy(int_array, int_array + 10, int_vec.begin());

    std::println("int_vec following copy() is: {}", int_vec);

    copy(int_list.begin(), int_list.end(), int_array);

    std::println("int_array following copy() is...");

    for (int i = 0; i < 10; ++i)
    {
        std::println("int_array[{}] is: {}", i, int_array[i]);
    }

    /*==============================================================================*
    *                                    Drill 8                                    *
    *                                                                               *
    *[8] Use std::find() to see if the vector contains the value 3 and print out its*
    * position if it does; use find() to see if the list contains the value 27 and  *
    * print out its position if it does. The “position” of the first element is 0,  *
    * the position of the second element is 1, etc. Note that if find() returns the *
    *                 end of the sequence, the value wasn’t found.                  *
     *==============================================================================*/

    auto vec_three = std::find(int_vec.begin(), int_vec.end(), 3);
    // doing it manually:
    if (vec_three != int_vec.end())
    {
        auto position = vec_three - int_vec.begin();
        std::println("found {} at position {}", *vec_three, position);
    }
    else
    {
        std::println("not found");
    }
    // using std::distance()
    if (vec_three != int_vec.end())
    {
        auto position = std::distance(int_vec.begin(), vec_three);
        std::println("found {} at position {}", *vec_three, position);
    }

    auto list_tsev = std::find(int_list.begin(), int_list.end(), 27);
    std::println("find() 27 in list... result: {}", *list_tsev);

    if (list_tsev != int_list.end())
    {
        auto position = std::distance(int_list.begin(), list_tsev);
        std::println("found {} at position {}", *list_tsev, position);
    }
    else 
    {
        std::println("27 not found");
    }

    return 0;
}