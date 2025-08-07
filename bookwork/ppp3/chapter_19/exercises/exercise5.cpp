import std;

/*=============================================================*
*                          Exercise 5                          *
*                                                              *
*Define an input and an output operator (>> and <<) for vector.*
 *=============================================================*/

 template<typename T>
 std::istream& operator>>(std::istream& ist, std::vector<T>& vec)
 {
    double input{};
    while(ist >> input)
    {
        vec.push_back(input);
    }
    return ist;
 }

 template<typename T>
 std::ostream& operator<<(std::ostream& ost, std::vector<T>& vec)
 {
    ost << "[";
    for (std::size_t i = 0; i < vec.size(); ++i)
    {
        ost << vec[i];
        if (vec[i] != *(vec.end() - 1))
        {
            ost << ", ";
        }
    }
    ost << "]";
    return ost;
}

int main()
{
    std::vector double_vec{ 3.14, 9.8, 1.3, 0.618 };
    std::cout << double_vec << '\n';

    std::println("Enter some double values. Ctrl + D to end input.");
    std::cin >> double_vec;

    std::cout << double_vec;

    return 0;
}