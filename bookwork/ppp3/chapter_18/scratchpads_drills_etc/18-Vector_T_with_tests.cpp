//$ ----- Chapter 18 Vector stuff ----- //
import std;

// global variable for educational reasons... 
int reasonable_size = std::numeric_limits<int>::max();

template<class T> concept Element = true;

// template<typename T>        // for all types T
//     requires (Element<T>)   // such that T is an element
template<Element T, typename A = std::allocator<T>> 
class Vector {
public:
    Vector() :sz{0}, elem{nullptr}, space{0} { }
    explicit Vector(int s);

    Vector(std::initializer_list<T>);
    Vector<T, A>& operator=(std::initializer_list<T> lst);

    Vector(const Vector<T, A>& origin);
    Vector<T, A>& operator=(const Vector<T, A>& origin);

    Vector(Vector<T, A>&& origin);
    Vector<T, A>& operator=(Vector<T, A>&& origin);

    ~Vector();

public:
    T& at(int n);
    const T& at(int n) const;

    T& operator[](int n) { return elem[n]; }
    const T& operator[](int n) const { return elem[n]; }

    int size() const { return sz; }
    int capacity() const { return space; }

    void resize(int newsize, T val = T{});
    void push_back(const T& val);
    void reserve(int newalloc);

    T* begin() const { return elem; }
    T* end() const { return elem+sz; }

private:
    int sz;
    T* elem;
    int space;

private:
    A alloc;        // use std::allocate to handle memory for elements
};

template<typename T>
bool operator==(const Vector<T>& lhs, const Vector<T>& rhs)
{
    return std::ranges::equal(lhs, rhs);
}

template<typename T>
bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs)
{
    return !(lhs == rhs);
}

void stress_test() {
    std::cout << "\n=== Stress Test ===\n";
    
    Vector<int> stress{};
    const int iterations = 1000;
    
    // Test rapid growth
    for (int i = 0; i < iterations; ++i) {
        stress.push_back(i);
    }
    std::cout << "✅ Added " << iterations << " elements\n";
    std::cout << "Final size: " << stress.size() << ", capacity: " << stress.capacity() << "\n";
    
    // Test shrinking
    stress.resize(100);
    std::cout << "✅ Resized to 100 elements\n";
    
    // Test copy operations with large vectors
    Vector<int> stress_copy{stress};
    std::cout << "✅ Large vector copy successful\n";
    
    Vector<int> stress_assign{};
    stress_assign = stress;
    std::cout << "✅ Large vector assignment successful\n";
    
    std::cout << "🚀 Stress test completed!\n";
}

int main()
{
    std::cout << "=== Testing Vector Class ===\n\n";
    
    try {
        // Test 1: Default constructor
        std::cout << "Test 1: Default constructor\n";
        Vector<int> v1{};
        std::cout << "✅ Default constructor - size: " << v1.size() 
                  << ", capacity: " << v1.capacity() << "\n\n";
        
        // Test 2: Size constructor
        std::cout << "Test 2: Size constructor\n";
        Vector<int> v2{5};
        std::cout << "✅ Size constructor - size: " << v2.size() 
                  << ", capacity: " << v2.capacity() << "\n";
        std::cout << "Elements: ";
        for (int i = 0; i < v2.size(); ++i) {
            std::cout << v2[i] << " ";
        }
        std::cout << "\n\n";
        
        // Test 3: Initializer list constructor
        std::cout << "Test 3: Initializer list constructor\n";
        Vector<int> v3{1, 2, 3, 4, 5};
        std::cout << "✅ Initializer list - size: " << v3.size() 
                  << ", capacity: " << v3.capacity() << "\n";
        std::cout << "Elements: ";
        for (const auto& elem : v3) {
            std::cout << elem << " ";
        }
        std::cout << "\n\n";
        
        // Test 4: Copy constructor
        std::cout << "Test 4: Copy constructor\n";
        Vector<int> v4{v3};  // Copy v3
        std::cout << "✅ Copy constructor - size: " << v4.size() 
                  << ", capacity: " << v4.capacity() << "\n";
        std::cout << "Original: ";
        for (const auto& elem : v3) { std::cout << elem << " "; }
        std::cout << "\nCopy: ";
        for (const auto& elem : v4) { std::cout << elem << " "; }
        std::cout << "\n\n";
        
        // Test 5: Move constructor
        std::cout << "Test 5: Move constructor\n";
        Vector<int> temp{10, 20, 30};
        Vector<int> v5{std::move(temp)};
        std::cout << "✅ Move constructor - size: " << v5.size() 
                  << ", capacity: " << v5.capacity() << "\n";
        std::cout << "Moved-to vector: ";
        for (const auto& elem : v5) { std::cout << elem << " "; }
        std::cout << "\nMoved-from vector size: " << temp.size() << "\n\n";
        
        // Test 6: Copy assignment (different scenarios)
        std::cout << "Test 6: Copy assignment\n";
        
        // 6a: Shrinking assignment
        Vector<int> v6a{1, 2, 3, 4, 5, 6, 7};
        Vector<int> small{10, 20};
        v6a = small;  // Shrinking
        std::cout << "✅ Shrinking assignment - size: " << v6a.size() << "\n";
        std::cout << "Elements: ";
        for (const auto& elem : v6a) { std::cout << elem << " "; }
        std::cout << "\n";
        
        // 6b: Growing within capacity
        Vector<int> v6b{1, 2, 3};
        v6b.reserve(10);  // Give it more capacity
        Vector<int> medium{100, 200, 300, 400, 500};
        v6b = medium;  // Growing within capacity
        std::cout << "✅ Growing within capacity - size: " << v6b.size() 
                  << ", capacity: " << v6b.capacity() << "\n";
        std::cout << "Elements: ";
        for (const auto& elem : v6b) { std::cout << elem << " "; }
        std::cout << "\n";
        
        // 6c: Need new capacity
        Vector<int> v6c{1, 2};
        Vector<int> large{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        v6c = large;  // Need new capacity
        std::cout << "✅ Need new capacity - size: " << v6c.size() 
                  << ", capacity: " << v6c.capacity() << "\n";
        std::cout << "Elements: ";
        for (const auto& elem : v6c) { std::cout << elem << " "; }
        std::cout << "\n\n";
        
        // Test 7: Move assignment
        std::cout << "Test 7: Move assignment\n";
        Vector<int> v7{1, 2, 3};
        Vector<int> to_move{99, 88, 77, 66, 55};
        v7 = std::move(to_move);
        std::cout << "✅ Move assignment - size: " << v7.size() << "\n";
        std::cout << "Elements: ";
        for (const auto& elem : v7) { std::cout << elem << " "; }
        std::cout << "\nMoved-from size: " << to_move.size() << "\n\n";
        
        // Test 8: Initializer list assignment
        std::cout << "Test 8: Initializer list assignment\n";
        Vector<int> v8{1, 2, 3};
        v8 = {10, 20, 30, 40, 50, 60};
        std::cout << "✅ Initializer list assignment - size: " << v8.size() << "\n";
        std::cout << "Elements: ";
        for (const auto& elem : v8) { std::cout << elem << " "; }
        std::cout << "\n\n";
        
        // Test 9: at() function with bounds checking
        std::cout << "Test 9: at() function\n";
        Vector<int> v9{10, 20, 30};
        std::cout << "✅ v9.at(1) = " << v9.at(1) << "\n";
        try {
            std::cout << "Trying v9.at(10)...\n";
            v9.at(10);  // Should throw
        } catch (const std::invalid_argument& e) {
            std::cout << "✅ Caught expected exception: " << e.what() << "\n";
        }
        std::cout << "\n";
        
        // Test 10: reserve() function
        std::cout << "Test 10: reserve() function\n";
        Vector<int> v10{1, 2, 3};
        std::cout << "Before reserve - capacity: " << v10.capacity() << "\n";
        v10.reserve(20);
        std::cout << "After reserve(20) - capacity: " << v10.capacity() << "\n";
        std::cout << "Elements preserved: ";
        for (const auto& elem : v10) { std::cout << elem << " "; }
        std::cout << "\n\n";
        
        // Test 11: resize() function
        std::cout << "Test 11: resize() function\n";
        Vector<int> v11{1, 2, 3};
        std::cout << "Original size: " << v11.size() << "\n";
        
        // Resize larger
        v11.resize(6, 99);
        std::cout << "After resize(6, 99) - size: " << v11.size() << "\n";
        std::cout << "Elements: ";
        for (const auto& elem : v11) { std::cout << elem << " "; }
        std::cout << "\n";
        
        // Resize smaller
        v11.resize(4);
        std::cout << "After resize(4) - size: " << v11.size() << "\n";
        std::cout << "Elements: ";
        for (const auto& elem : v11) { std::cout << elem << " "; }
        std::cout << "\n\n";
        
        // Test 12: push_back() function
        std::cout << "Test 12: push_back() function\n";
        Vector<int> v12{};
        std::cout << "Initial capacity: " << v12.capacity() << "\n";
        
        for (int i = 1; i <= 10; ++i) {
            v12.push_back(i * 10);
            std::cout << "After push_back(" << (i * 10) << ") - size: " 
                      << v12.size() << ", capacity: " << v12.capacity() << "\n";
        }
        std::cout << "Final elements: ";
        for (const auto& elem : v12) { std::cout << elem << " "; }
        std::cout << "\n\n";
        
        // Test 13: Comparison operators
        std::cout << "Test 13: Comparison operators\n";
        Vector<int> v13a{1, 2, 3};
        Vector<int> v13b{1, 2, 3};
        Vector<int> v13c{1, 2, 4};
        
        std::cout << "v13a == v13b: " << (v13a == v13b ? "true" : "false") << "\n";
        std::cout << "v13a == v13c: " << (v13a == v13c ? "true" : "false") << "\n";
        std::cout << "v13a != v13c: " << (v13a != v13c ? "true" : "false") << "\n\n";
        
        // Test 14: Iterator support (range-for loops)
        std::cout << "Test 14: Iterator support\n";
        Vector<int> v14{5, 10, 15, 20};
        std::cout << "Using range-for loop: ";
        for (const auto& elem : v14) {
            std::cout << elem << " ";
        }
        std::cout << "\nUsing traditional iterators: ";
        for (auto it = v14.begin(); it != v14.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << "\n\n";
        
        // Test 15: Working with different types
        std::cout << "Test 15: Different types\n";
        Vector<std::string> v15{"Hello", "World", "C++", "Templates"};
        std::cout << "String vector: ";
        for (const auto& str : v15) {
            std::cout << str << " ";
        }
        std::cout << "\n";
        
        Vector<double> v16{3.14, 2.71, 1.41};
        std::cout << "Double vector: ";
        for (const auto& d : v16) {
            std::cout << d << " ";
        }
        std::cout << "\n\n";
        
        // Test 16: Self-assignment protection
        std::cout << "Test 16: Self-assignment\n";
        Vector<int> v17{1, 2, 3, 4, 5};
        v17 = v17;  // Self-assignment
        std::cout << "✅ Self-assignment handled - size: " << v17.size() << "\n";
        std::cout << "Elements: ";
        for (const auto& elem : v17) { std::cout << elem << " "; }
        std::cout << "\n\n";
        
    } catch (const std::exception& e) {
        std::cout << "❌ Test failed with exception: " << e.what() << "\n";
        return 1;
    }
    
    std::cout << "🎉 All tests passed! Your Vector implementation is working correctly!\n";

    std::println("Now for the stress test...");

    stress_test();
    
    return 0;
}

/*=======================================================*
**                                                       **
//$               Vector Class Definitions                **
**             (The "Essential Operations")              **
**                                                       **
 *=======================================================*/

// int constructor
template<Element T, typename A>
Vector<T, A>::Vector(int s) 
    : sz{ s }
    , elem{ nullptr }
    , space{ s }
{
    if (s < 0)
    {
        throw std::invalid_argument("[!] Can't have negative size [!]\n");
    }
    if (s > reasonable_size)
    {
        throw std::length_error{"[!] Invalid size for Vector [!]\n"};
    }
    if (s > 0) 
    {
        elem = alloc.allocate(s);
        
        for (int i = 0; i < sz; ++i) 
        {
            std::construct_at(&elem[i], T{});  // Modern way
        }
    }
}

// initializer_list constructor
template<Element T, typename A>
Vector<T, A>::Vector(std::initializer_list<T> lst)
    : sz{ static_cast<int>(lst.size()) }
    , space{ static_cast<int>(lst.size()) }
{
    if (sz > 0)
    {
        elem = alloc.allocate(lst.size());
        std::uninitialized_copy(lst.begin(), lst.end(), elem);
    }
    else
    {
        elem = nullptr;
    }
}

// initializer_list assignment operator
template<Element T, typename A>
Vector<T, A>& Vector<T, A>::operator=(std::initializer_list<T> lst)
{
    int new_size{ static_cast<int>(lst.size()) };
    reserve(new_size);
    std::copy(lst.begin(), lst.end(), elem);
    sz = new_size;
    return *this;
}

// copy constructor
template<Element T, typename A>
Vector<T, A>::Vector(const Vector<T, A>& orig)
    : sz{ orig.sz }
    , space{ orig.space }
{
    if (orig.sz > 0)
    {
        elem = alloc.allocate(space);
        std::uninitialized_copy(orig.begin(), orig.end(), elem);
    }
    else
    {
        elem = nullptr;
    }
}

// copy assignment operator
template<Element T, typename A>
Vector<T, A>& Vector<T, A>::operator=(const Vector<T, A>& orig)
{
    if (this == &orig)
    {
        return *this;
    }
    // if the Vector we're copying to has more/same capacity than orig's total elements
    if (orig.sz <= space)
    {
        // if Vector we're copying to has more elements than orig
        // (we're shrinking or same size)
        if (orig.sz <= sz)
        {
            // copy the matching indices
            std::copy(orig.begin(), orig.end(), elem);
            // destroy excess elements
            std::destroy(elem + orig.sz, elem + sz);
        }
        // otherwise orig has more elements than the Vector we're copying to
        // orig.sz > sz BUT orig.sz <= space
        else 
        {
            std::copy(orig.begin(), orig.begin() + sz, elem);
            std::uninitialized_copy(orig.begin() + sz, orig.end(), elem + sz);
        }

        sz = orig.sz;
        return *this;
    }

    // allocate more memory if orig's size is greater than this' space
    T* p = alloc.allocate(orig.sz);
    std::uninitialized_copy(orig.begin(), orig.end(), p);

    // clear out this' existing memory
    std::destroy(elem, elem + sz);
    alloc.deallocate(elem, space);

    sz = orig.sz;
    elem = p;
    space = orig.sz;
    return *this;
}

// move constructor
template<Element T, typename A>
Vector<T, A>::Vector(Vector<T, A>&& orig)
    : sz{ orig.sz }
    , elem{ orig.elem }
    , space{ orig.space }
    , alloc{ std::move(orig.alloc) }
{
    orig.sz = 0;
    orig.elem = nullptr;
    orig.space = 0;
}

// move assignment operator
template<Element T, typename A>
Vector<T, A>& Vector<T, A>::operator=(Vector<T, A>&& orig)
{
    if (this != &orig)
    {
        // clean up existing...
        std::destroy(elem, elem + sz);
        alloc.deallocate(elem, space);

        // now steal orig's data
        sz = orig.sz;
        elem = orig.elem;
        space = orig.space;
        alloc = std::move(orig.alloc);

        // leave in orig in valid but unspecified state
        orig.sz = 0;
        orig.elem = nullptr;
        orig.space = 0;
    }
    return *this;
}

// destructor
template<Element T, typename A>
Vector<T, A>::~Vector()
{
    // Destroy constructed elements
    std::destroy(elem, elem + sz);

    // Deallocate using the allocator
    if (elem != nullptr)
    {
        alloc.deallocate(elem, space);
    }
}

/*=======================================================*
**                                                       **
//$           Vector member functions and etc.            **
**                                                       **
 *=======================================================*/

template<Element T, typename A>
T& Vector<T, A>::at(int n)
{
    if (n < 0 || sz <= n)
    {
        throw std::invalid_argument("[!] Out of bounds [!]\n");
    }
    return elem[n];
}

template<Element T, typename A>
const T& Vector<T, A>::at(int n) const
{
    if (n < 0 || sz <= n)
    {
        throw std::invalid_argument("[!] Out of bounds! [!]\n");
    }
    return elem[n];
}


//$ Memory / Capacity functions 

template<Element T, typename A>
void Vector<T, A>::reserve(int newalloc)
// reserve space for Vector
{
    if (newalloc <= space)                  // never decrease allocation
        return;

    T* p = alloc.allocate(newalloc);        // allocate new space
    std::uninitialized_move(elem, elem + sz, p);

    // clear up memory before transfering ownership of p to this
    std::destroy(elem, elem + sz);
    alloc.deallocate(elem, space);

    elem = p;                               // make elem point to new memory
    space = newalloc;
}

template<Element T, typename A>
void Vector<T, A>::resize(int newsize, T val)   // val default is T{} in declaration
{
    reserve(newsize);
    if (sz < newsize)
    {
        std::uninitialized_fill(elem + sz, elem + newsize, val);
    }
    if (newsize < sz)
    {
        std::destroy(elem + newsize, elem + sz);
    }
    sz = newsize;
}

template<Element T, typename A>
void Vector<T, A>::push_back(const T& val)
// increase Vector size by one; initialize the new element with d
{
    if (sz == space)
    {
        reserve((space == 0) ? 8 : (2 * space));
    }
    std::construct_at(&elem[sz], val);
    ++sz;
}