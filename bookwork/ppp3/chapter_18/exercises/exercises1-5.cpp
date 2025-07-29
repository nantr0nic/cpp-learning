#include <linux/limits.h>
import std;

/*======================================================================*
*                              Exercise 1                               *
*Write a template function add() that adds the elements of one vector<T>*
*     to the elements of another; for example, add(v1,v2) should do     *
*                 v1[i]+=v2[i] for each element of v1.                  *
 *======================================================================*/
// My note: doesn't say if this should be void or return a vector, so I'll
// write both

 template <typename T>
 void add(std::vector<T>& v1, const std::vector<T>& v2)
 // This will add v2 TO v1
 {
    if (v1.empty() || v2.empty())
    {
        std::println("[!] Error: can't add empty vector [!]");
        return;     // avoiding throwing where possible
    }
    // If v2 has more elements, resize for extra space on v1 (if required)
    // I think we'll just add v2 elements to the 0-init'd v1 elements
    if (v2.size() > v1.size())
    {
        v1.resize(v2.size());
    }
    // If v2 has fewer elements, its elements will be added to
    // v1's but the remaining v1 elements will stay as they are
    for (std::size_t i = 0; i < v1.size(); ++i)
    {
        v1[i] += v2[i];
    }
}

template <typename T>
std::vector<T> add_make_vec(const std::vector<T>& v1, const std::vector<T>& v2)
// This returns a vector that is populated with v1[i] + v2[i]
{
    if (v1.empty() || v2.empty())
    {
        throw std::invalid_argument("[!] Error: can't add empty vector [!]");
    }
    std::size_t max_size{std::max(v1.size(), v2.size())};
    std::vector<T> temp;
    temp.reserve(max_size);

    for (std::size_t i = 0; i < max_size; ++i)
    {
        // handle if we're past one of the vector's elements
        // if so, default to the type's default value
        T val1{ (i < v1.size()) ? v1[i] : T{} };
        T val2{ (i < v2.size()) ? v2[i] : T{} };
        temp.push_back(val1 + val2);
    }

    return temp;
}

/*========================================================================*
*                               Exercise 2                                *
*                                                                         *
*Write a template function that takes a vector<T> vt and a vector<U> vu as*
*           arguments and returns the sum of all vt[i]*vu[i]s.            *
 *========================================================================*/

 // My note: the textbook didn't go over examples of handling different types
 // within the same template but I'm gonna go for it. Hopefully I'm not
 // misunderstanding the requirements of this exercise...

template <typename T>
concept NumericMath = (std::integral<T> || std::floating_point<T>)
    && !std::same_as<T, bool>
    && !std::same_as<T, char>
    && !std::same_as<T, signed char>
    && !std::same_as<T, unsigned char>;

// This function will return the sum of all vt[i] * vu[i] in the form of whichever
// type is larger (so double if using int and double, long long if vs. int)
template<NumericMath T, NumericMath U>
auto sum_vec_multiples(const std::vector<T>& vt, const std::vector<U>& vu)
    -> std::conditional_t<(sizeof(T) > sizeof(U)), T, U>
{
    // For this function we'll make the requirement that their sizes match
    // because if they don't then initializing new elements to 0 will make
    // the products 0 anyway...
    if (vt.size() != vu.size())
    {
        throw std::invalid_argument("[!] Vectors must have the same size [!]");
    }
    // This is a cleaner than the comment block below
    using ResultType = std::conditional_t<(sizeof(T) > sizeof(U)), T, U>;
    ResultType result {};

    for (std::size_t i = 0; i < vt.size(); ++i)
    {
        result += static_cast<ResultType>(vt[i]) * static_cast<ResultType>(vu[i]);
    }
    return result;

    /*
    if constexpr (sizeof(T) > sizeof(U))
    {
        T result_T {};
        for (std::size_t i = 0; i < vt.size(); ++i)
        {
            result_T += vt[i] * vu[i];
        }
        return result_T;
    }
    else 
    {
        U result_U {};
        for (std::size_t i = 0; i < vt.size(); ++i)
        {
            result_U += vt[i] * vu[i];
        }
        return result_U;
    }
    */
}

// And, just to be thorough and to cover any possible misunderstanding...
// This will return a vector of the larger type where result[i] = vt[i] * vu[i]
template <NumericMath T, NumericMath U>
auto sum_vec_multiples_new(const std::vector<T>& vt, const std::vector<U>& vu)
    -> std::conditional_t<(sizeof(T) > sizeof(U)), std::vector<T>, std::vector<U>>
{
    // We'll make the same requirement here regarding size
    if (vt.size() != vu.size())
    {
        throw std::invalid_argument("[!] Vectors must have same size [!]");
    }
    // Same technique as above
    using ResultType = std::conditional_t<(sizeof(T) > sizeof(U)), T, U>;

    std::vector<ResultType> temp;
    temp.reserve(vt.size());

    for (std::size_t i = 0; i < vt.size(); ++i)
    {
        temp.push_back(
            static_cast<ResultType>(vt[i]) * static_cast<ResultType>(vu[i])
        );
    }

    return temp;
}

                    /*=====================*
                    *      Exercise 3      *
                    *Skipping this exercise*
                    *=====================*/

/*===================================================================*
*                             Exercise 4                             *
*Modify class Link from §15.7 to be a template with the type of value*
*  as the template argument. Then redo exercise 13 from Chapter 16   *
*                          with Link<God>.                           *
 *===================================================================*/
// Exercise 13 from Chapter 16 is the Wumpus game and has nothing to do
// with this so I'm assuming this is a mistake in the book.
// Exercise 13 from Chapter 15 is implemented here... So I don't know
// what Bjarne was intending. The "God" struct exercises is only possible
// with strings (names of gods, mythologies, vehicles, and weapons) so
// I don't know what is possible here besides testing this template with
// a God struct outside of the Link class? I'm going to move on.

 template <typename T>
 class Link 
 {
    public:
    T value;

    Link(const T& v, Link* p = nullptr, Link* s = nullptr)
        : value{ v }, prev{ p }, succ{ s } { }

    Link* insert(Link* n);                          // insert n before this object
    Link* add(Link* n);                             // insert n after this object
    Link* erase();                                  // remove this object from list

    Link* find(const T& s);               // find s in list
    const Link* find(const T& s) const;   // find s in const list (see _oper.const_)

    Link* advance(int n); //const;                  // move n positions in list
    Link* next() const { return succ; }
    Link* previous() const { return prev; }

private:
    Link* prev;
    Link* succ;
};

template <typename T>
void print_all(Link<T>* p)
{
    std::cout << "{ ";
    while (p)
    {
        std::cout << p->value;
        if ((p = p->next()))
            std::cout << ", ";
    }
    std::cout << " }";
}

// ----- Link Definitions ----- //
template <typename T>
Link<T>* Link<T>::insert(Link<T>* n)         // insert n before this object; return n
{
    if (n == nullptr)               // nothing to insert
        return this;
    n->succ = this;                 // p comes after n
    if (prev)
        prev->succ = n;
    n->prev = prev;                 // p's predecessor becomes n's predecessor
    prev = n;                       // n becomes p's predecessor
    return n;
}

template <typename T>
Link<T>* Link<T>::add(Link<T>* n)            // insert n after this object; return n
{
    if (n == nullptr)               // nothing to add
        return this;
    n->prev = this;                 // this comes before n
    n->succ = succ;                 // this' successor becomes n's successor (including nullptr)
    if (succ)                       // if this object has (non-null) successor,
        succ->prev = n;             // n becomes this's successor's predecessor
    succ = n;                       // this object's successor becomes n
    return n;
}

template <typename T>
Link<T>* Link<T>::erase()                 // remove this from list, return successor
{
    if (succ)                       // if this has a successor
        succ->prev = prev;          // set successor's predecessor to this' predecessor
    if (prev)                       // if this has predecessor
        prev->succ = succ;          // set predecessor's successor to this' successor
    return succ;
}

template <typename T>
Link<T>* Link<T>::find(const T& s)      // find s in list, return nullptr if not found
{
    Link<T>* current = this;
    while (current)                         // while current != nullptr
    {
        if (current->value == s)            // if found
            return current;                 // return it
        current = current->succ;            // if not, move on to successor (until nullptr)
    }
    return nullptr;
}

template <typename T>
Link<T>* Link<T>::advance(int n)          // move n positions in list; return nullptr for "not found"
{                                   // positive n moves forward, negative backward
    Link* p = this;
    if (p == nullptr)
        return nullptr;
    while (0 < n)
    {
        --n;
        if (p->succ)
            p = p->succ;
        else
            return nullptr;
    }
    while (n < 0)
    {
        ++n;
        if (p->prev)
            p = p->prev;
        else
            return nullptr;
    }
    return p;
}

/*======================================================================*
*                              Exercise 5                               *
*    Define a class Int having a single member of class int. Define     *
*constructors, assignment, and operators +, −, *, / for it. Test it, and*
*  improve its design as needed (e.g., define operators << and >> for   *
*                           convenient I/O).                            *
 *======================================================================*/
 // I'm going to make 'value' public cuz this is an Int class lol
struct Int 
{
public:
    int value{ 0 };

    Int() : value{ 0 } {}
    explicit Int(int val) : value{ val } {}

    Int(const Int& orig) : value{ orig.value } {}
    Int& operator=(const Int& orig) { value = orig.value; return *this; }
    Int(Int&& orig) noexcept : value{ orig.value } {}
    Int& operator=(Int&& orig) noexcept { value = orig.value; return *this; }

    // operations with built-in ints
    // handles Int = Int + int
    Int operator+(int num) const { return Int{ value + num }; }
    Int operator-(int num) const { return Int{ value - num }; }
    Int operator*(int num) const { return Int{ value * num }; }
    Int operator/(int num) const {
        if (num == 0)
        {
            throw std::invalid_argument("[!] Can't divide by 0 [!]");
        }
        return Int{ value / num };
    }

    // operations with Int type
    Int operator+(const Int& other_Int) const { return Int{ value + other_Int.value }; }
    Int operator-(const Int& other_Int) const { return Int{ value - other_Int.value }; }
    Int operator*(const Int& other_Int) const { return Int{ value * other_Int.value }; }
    Int operator/(const Int& other_Int) const {
        if (other_Int.value == 0)
        {
            throw std::invalid_argument("[!] Can't divide by 0 [!]");
        }
        return Int{ value / other_Int.value };
    }

    // compound assignment operators with ints
    Int& operator+=(int num) { value += num; return *this; }
    Int& operator-=(int num) { value -= num; return *this; }
    Int& operator*=(int num) { value *= num; return *this; }
    Int& operator/=(int num) { 
        if (num == 0) {
            throw std::invalid_argument("[!] Can't divide by 0 [!]");
        }
        value /= num; 
        return *this; 
    }

    // compound assignment operators with Int types
    Int& operator+=(const Int& other_Int) { value += other_Int.value; return *this; }
    Int& operator-=(const Int& other_Int) { value -= other_Int.value; return *this; }
    Int& operator*=(const Int& other_Int) { value *= other_Int.value; return *this; }
    Int& operator/=(const Int& other_Int) { 
        if (other_Int.value == 0) {
            throw std::invalid_argument("[!] Can't divide by 0 [!]");
        }
        value /= other_Int.value; 
        return *this; 
    }


};

// Free functions that cover Int = int + Int
Int operator+(int num, const Int& int_obj)
{
    return Int{num + int_obj.value};
}

Int operator*(int num, const Int& int_obj)
{
    return Int{num * int_obj.value};
}

std::ostream& operator<<(std::ostream& os, const Int& int_class)
{
    os << int_class.value;
    return os;
}

std::istream& operator>>(std::istream& is, Int& int_class)
{
    int input_num{};
    is >> input_num;
    int_class.value = input_num;
    return is;
}

bool operator==(const Int& lhs, const Int& rhs)
{
    return lhs.value == rhs.value;
}
bool operator!=(const Int& lhs, const Int& rhs)
{
    return !(lhs == rhs);
}
bool operator<(const Int& lhs, const Int& rhs)
{
    return lhs.value < rhs.value;
}
bool operator>(const Int& lhs, const Int& rhs)
{
    return lhs.value > rhs.value;
}
bool operator<=(const Int& lhs, const Int& rhs)
{
    return !(lhs > rhs);
}
bool operator>=(const Int& lhs, const Int& rhs)
{
    return !(lhs < rhs);
}


/*=======================================================*
**                                                       **
**          Exercises tests -- main() function           **
**                                                       **
 *=======================================================*/

int main()
{
    //$ ----- Exercise 1 -----
    std::println("<==== Exercise 1 Tests ====>");
    std::println("    (First template)     ");
    // Test basic functions with double type, I'll do it in the written order
    std::vector<double> vec_d1{ 1, 2, 3, 4, 5 };
    std::vector<double> vec_d2{ 1, 2, 3, 4, 5 };
    std::vector<double> vec_d3;
    std::vector<double> vec_d4{ 0, 0, 0 };

    std::println("Error should be printed...");
    add(vec_d3, vec_d4);
    
    std::println("Before add(), d4's size is: {}\n{}", vec_d4.size(), vec_d4);
    add(vec_d4, vec_d1);
    std::println("After add(), d4's size is: {}\n{}", vec_d4.size(), vec_d4);

    std::println("vec_d1 and vec_d2 are: {}, {}", vec_d1, vec_d2);
    add(vec_d1, vec_d2);
    std::println("after add(), vec_d1 and vec_d2 are: {}, {}", vec_d1, vec_d2);

    std::vector<char> vec_char1 {'a', 'b', 'c', 'd'};
    std::vector<char> vec_char2 {'a', 'b', 'c', 'd'};
    std::println("\nTesting what happens with vector<char> {}", vec_char1);
    add(vec_char1, vec_char2);
    std::println("{}", vec_char1);

    std::vector<std::string> vec_string1{"This is", "the first vector", "of strings"};
    std::vector<std::string> vec_string2{"This is", "the SECOND vector", "of strings"};
    std::println("Testing what happens with vector<string> {}", vec_string1);
    add(vec_string1, vec_string2);
    std::println("{}", vec_string1);

    // second template
    std::println("\n      (Second template)    ");
    std::println("vec_d2 and vec_d4 are: {} {}", vec_d2, vec_d4);
    std::vector<double> d2_d4{ add_make_vec(vec_d2, vec_d4) };
    std::println("new vec d2_d4 is produced: {}", d2_d4);
    std::println("Testing with previous strings.");
    std::vector<std::string> vec_string_result{ add_make_vec(vec_string1, vec_string2) };
    std::println("Result: {}", vec_string_result);

    //$ ----- Exercise 2 tests -----
    std::println("\n\n     Exercise 2     ");
    std::println("     (First template)    ");
    std::vector<int> vec_int1{ 0, 0, 0 };
    std::vector<int> vec_int2{ 1, 2, 3, 4, 5 };
    std::vector<double> vec_d5{ 1.1, 2.2, 3.3, 4.4, 5.5 };
    std::vector<long long> vec_l_l{ 111, 222, 333, 444, 555 };
    // sum_vec_multiples(vec_int1, vec_string_result); //! correctly fails to be allowed!
    //! VVV int correctly returns narrowing conversion warning! VVV
    auto sum_result = sum_vec_multiples(vec_d5, vec_int2);
    std::println("Added vec_d5 and vec_int2. Result: {}", sum_result);
    std::println("     (Second Template)    ");
    std::vector<long long> result_test{ sum_vec_multiples_new(vec_d5, vec_l_l) };
    std::println("Adding vec_d5 and vec_l_l. New vector: {}", result_test);

    std::println("Trying matching size throw");
    try {
        sum_result = sum_vec_multiples(vec_d5, vec_int1);
    }
    catch (std::invalid_argument& e)
    {
        std::println("{}", e.what());
    }


    return 0;
}