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


int main()
{

    Vector<std::string> some_words;
    some_words.reserve(8);
    some_words.resize(0);
    some_words.push_back("I really hope ");
    some_words.push_back("that this works...");
    std::println("{}", some_words);
    // woo it does!

    Vector<Vector<std::string>> aVectorVector;
    Vector<std::string> more_words {"What about", "this here...", "does it work?!"};
    aVectorVector.push_back(some_words);
    aVectorVector.push_back(more_words);
    std::println("{}", aVectorVector);

    std::println("Omg it does :) <3 !!!");
    
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