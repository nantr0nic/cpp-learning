import std;

template<typename T>
struct S
{
public:
    S(T val = T{}) : value{ val } {}
    S& operator=(const S& orig);

    T& access();
    T access() const;

    void read_val();

private:
    T value;

};

template<typename T>
S<T>& S<T>::operator=(const S& orig)
{
    T tmp = orig.value;
    value = tmp;
    return *this;
}

template<typename T>
T& S<T>::access()
{
    return value;
}

template<typename T>
T S<T>::access() const
{
    return value;
}

template<typename T>
void read_val(T& v)
{
    std::cin >> v;
}

template<typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& vec_T)
{
    T input{};
    while (is >> input)
    {
        vec_T.push_back(input);

        if (is.peek() == '\n')
        {
            is.ignore();
            break;
        }
    }
    return is;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T>& vec_T)
{
    os << "[";
    for (const T& e : vec_T)
    {
        os << e << ','; 
    }
    os << "]";
    return os;
}

template<typename T>
void S<T>::read_val()
{
    T tmp{ T{} };
    std::cin >> tmp;
    value = tmp;
}


int main()
{
    S<int> sint(1);
    S<char> schar('2');
    S<double> sdoub(3.00);
    S<std::string> sstring("4.0");
    std::vector<int> vint{ 5, 6, 7, 8 };
    S<std::vector<int>>  svint(vint);
    
    std::string input_string;
    std::print("enter some text: "); read_val(input_string);
    sstring.access() = input_string;
    

    S<char> schar2('X');
    schar2 = schar;

    using S_variant = std::variant<S<int>, S<char>, S<double>, S<std::string>, S<std::vector<int>>>;

    std::vector<S_variant> S_cont{ sint, schar, schar2, sdoub, sstring, svint };

    for (const auto& elem : S_cont)
    {
        std::visit([](const auto& s)
        {
            std::println("Value: {}", s.access());
        }, elem);
    }

    std::print("Read into schar: "); schar.read_val();
    std::print("Read into sdoub: "); sdoub.read_val();
    std::print("Read into sstring: "); sstring.read_val();
    std::print("Read into svint: "); svint.read_val();

    S_cont.clear();
    S_cont = { sint, schar, schar2, sdoub, sstring, svint };

    for (const auto& elem : S_cont)
    {
        std::visit([](const auto& s)
        {
            std::println("Value: {}", s.access());
        }, elem);
    }

    std::print("is_test1 (int): ");
    std::vector<int> is_test1{};
    std::cin >> is_test1;
    std::cout << "is_test1: " << is_test1 << '\n';

    std::print("is_test2 (string): ");
    std::vector<std::string> is_test2{};
    std::cin >> is_test2;
    std::cout << "is_test2: " << is_test2 << '\n';

    std::print("is_test3 (vector<char>): ");
    std::vector<char> is_test3;
    std::cin >> is_test3;
    std::cout << "is_test3: " << is_test3 << '\n';

    return 0;
}