import std;

/*===================================================================*
*                             Exercise 6                             *
*Repeat the previous exercise, but with a class Number<T> where T can*
*  be any numeric type. Try adding % to Number and see what happens  *
*     when you try to use % for Number<double> and Number<int>.      *
 *===================================================================*/

template <typename T>
concept NumericMath = (std::integral<T> || std::floating_point<T>)
    && !std::same_as<T, bool>
    && !std::same_as<T, char>
    && !std::same_as<T, signed char>
    && !std::same_as<T, unsigned char>;

template<NumericMath T>
struct Number
{
public:
    T value{ 0 };

    Number<T>() : value{ 0 } {}
    explicit Number<T>(T val) : value{ val } {}

    Number<T>(const Number<T>& orig) : value{ orig.value } {}
    Number<T>& operator=(const Number<T>& orig) { value = orig.value; return *this; }
    Number<T>(Number<T>&& orig) noexcept : value{ orig.value } {}
    Number<T>& operator=(Number<T>&& orig) noexcept { value = orig.value; return *this; }

    // operations with built-in numeric types
    // handles Number<T> = Number<T> + Number<T>
    Number<T> operator+(T num) const { return Number<T>{ value + num }; }
    Number<T> operator-(T num) const { return Number<T>{ value - num }; }
    Number<T> operator*(T num) const { return Number<T>{ value * num }; }
    Number<T> operator/(T num) const {
        if (num == 0)
        {
            throw std::invalid_argument("[!] Can't divide by 0 [!]");
        }
        return Number<T>{ value / num };
    }

    // operations with Number<T> type
    Number<T> operator+(const Number<T>& other_Number) const { return Number<T>{ value + other_Number.value }; }
    Number<T> operator-(const Number<T>& other_Number) const { return Number<T>{ value - other_Number.value }; }
    Number<T> operator*(const Number<T>& other_Number) const { return Number<T>{ value * other_Number.value }; }
    Number<T> operator/(const Number<T>& other_Number) const {
        if (other_Number.value == 0)
        {
            throw std::invalid_argument("[!] Can't divide by 0 [!]");
        }
        return Number<T>{ value / other_Number.value };
    }

    // compound assignment operators with built-in numeric types
    Number<T>& operator+=(T num) { value += num; return *this; }
    Number<T>& operator-=(T num) { value -= num; return *this; }
    Number<T>& operator*=(T num) { value *= num; return *this; }
    Number<T>& operator/=(T num) { 
        if (num == 0) {
            throw std::invalid_argument("[!] Can't divide by 0 [!]");
        }
        value /= num; 
        return *this; 
    }

    // compound assignment operators with Number<T> types
    Number<T>& operator+=(const Number<T>& other_Number) { value += other_Number.value; return *this; }
    Number<T>& operator-=(const Number<T>& other_Number) { value -= other_Number.value; return *this; }
    Number<T>& operator*=(const Number<T>& other_Number) { value *= other_Number.value; return *this; }
    Number<T>& operator/=(const Number<T>& other_Number) { 
        if (other_Number.value == 0) {
            throw std::invalid_argument("[!] Can't divide by 0 [!]");
        }
        value /= other_Number.value; 
        return *this; 
    }

    // modulo overloads
    // ignoring the 0 thing for brevity
    // modulo operator only works with integral types (not floating point!)
    // so must add concept
    Number<T> operator%(T num) const requires std::integral<T> { 
        return Number<T>{ value % num }; 
    }
    Number<T> operator%(const Number<T>& other_Number) const requires std::integral<T> {
         return Number<T>{ value % other_Number.value }; 
    }
    Number<T>& operator%(T num) requires std::integral<T> {
         value %= num; 
         return *this; 
    }
    Number<T>& operator%(const Number<T>& other_Number) requires std::integral<T> {
        value %= other_Number.value;
        return *this;
    }

};

// Free functions that cover Number<T> = Number<T> + Number<T>
template<NumericMath T>
Number<T> operator+(T num, const Number<T>& Number_obj)
{
    return Number<T>{num + Number_obj.value};
}

template<NumericMath T>
Number<T> operator*(T num, const Number<T>& Number_obj)
{
    return Number<T>{num * Number_obj.value};
}

template<NumericMath T>
std::ostream& operator<<(std::ostream& os, const Number<T>& Number_class)
{
    os << Number_class.value;
    return os;
}
template<NumericMath T>
std::istream& operator>>(std::istream& is, Number<T>& Number_class)
{
    T input_num{};
    is >> input_num;
    Number_class.value = input_num;
    return is;
}
template<NumericMath T>
bool operator==(const Number<T>& lhs, const Number<T>& rhs)
{
    return lhs.value == rhs.value;
}
template<NumericMath T>
bool operator!=(const Number<T>& lhs, const Number<T>& rhs)
{
    return !(lhs == rhs);
}
template<NumericMath T>
bool operator<(const Number<T>& lhs, const Number<T>& rhs)
{
    return lhs.value < rhs.value;
}
template<NumericMath T>
bool operator>(const Number<T>& lhs, const Number<T>& rhs)
{
    return lhs.value > rhs.value;
}
template<NumericMath T>
bool operator<=(const Number<T>& lhs, const Number<T>& rhs)
{
    return !(lhs > rhs);
}
template<NumericMath T>
bool operator>=(const Number<T>& lhs, const Number<T>& rhs)
{
    return !(lhs < rhs);
}


/*=======================================================*
**                  ------------------                   **
**                    Main() Function                    **
**                  ------------------                   **
 *=======================================================*/

 int main()
 {
    Number integer_type(5);
    Number double_type(5.55);

    auto integer_type2 = integer_type + 10;

    std::println("Making type2 from integer_type + 10 (should be 15): {}", integer_type2.value);

    auto integer_modulo1 = integer_type % 2;

    std::println("integer_type % 2 = (expecting 1) {}", integer_modulo1.value);

    //auto double_modulo2 = double_type % 2.0;

    std::println("Now trying with double type, what will happen?");

    // std::println("{}", integer_modulo2.value);

    std::println("A posthumous compiler error :/");

    double_type *= 2;

    std::println("double_type(5.55) *= 2 is: {}", double_type.value);

    std::println("After adding integral concept to modulo... Compiler provides relevant error!");


    return 0;
 }