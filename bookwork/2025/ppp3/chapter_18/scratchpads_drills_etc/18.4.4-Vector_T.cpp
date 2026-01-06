//$ ----- Chapter 18 Vector stuff ----- //
import std;

// global variable for educational reasons... 
int reasonable_size = std::numeric_limits<int>::max();

template<class T> concept Element = true;

template<typename T, typename A = std::allocator<T>>
struct Vector_rep {
    A alloc;        // allocator
    int sz;         // number of elements
    T* elem;        // start of allocation
    int space;      // amount of allocated space

    //! this constructor doesn't check for valid values of n
    Vector_rep(const A& a, int n)
        : alloc{ a }, sz{ n }, elem{ alloc.allocate(n) }, space{ n } {}
    
    ~Vector_rep() { 
        if (elem != nullptr) {
            alloc.deallocate(elem, static_cast<std::size_t>(space)); 
        }
    }
};

// template<typename T>        // for all types T
//     requires (Element<T>)   // such that T is an element
template<Element T, typename A = std::allocator<T>> 
class Vector {
    Vector_rep<T, A> r; //! single letter name is a bad practice
public:
    Vector() : r{A{}, 0} { }
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

    T& operator[](int n) { return r.elem[n]; }
    const T& operator[](int n) const { return r.elem[n]; }

    int size() const { return r.sz; }
    int capacity() const { return r.space; }

    void resize(int newsize, T val = T{});
    void push_back(const T& val);
    void reserve(int newalloc);

    T* begin() const { return r.elem; }
    T* end() const { return r.elem + r.sz; }
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
    : r{ A{}, s }
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
        for (int i = 0; i < r.sz; ++i) 
        {
            std::construct_at(&r.elem[i], T{});  // Modern way
        }
    }
}

// initializer_list constructor
template<Element T, typename A>
Vector<T, A>::Vector(std::initializer_list<T> lst)
    : r{ A{}, static_cast<int>(lst.size()) }
{
    if (r.sz > 0)
    {
        std::uninitialized_copy(lst.begin(), lst.end(), r.elem);
    }
    else
    {
        r.elem = nullptr;
    }
}

// initializer_list assignment operator
template<Element T, typename A>
Vector<T, A>& Vector<T, A>::operator=(std::initializer_list<T> lst)
{
    int new_size{ static_cast<int>(lst.size()) };
    reserve(new_size);
    std::copy(lst.begin(), lst.end(), r.elem);
    r.sz = new_size;
    return *this;
}

// copy constructor
template<Element T, typename A>
Vector<T, A>::Vector(const Vector<T, A>& orig)
    : r{ A{}, orig.r.sz }
{
    if (orig.r.sz > 0)
    {
        std::uninitialized_copy(orig.begin(), orig.end(), r.elem);
    }
    else
    {
        r.elem = nullptr;
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
    
    if (orig.size() <= size())      // enough space; copy directly
    {
        std::copy(orig.r.elem, orig.r.elem + orig.size(), r.elem);
        std::destroy(r.elem + orig.size(), r.elem + size());    // destroy surplus elements
    }

    auto tmp = orig;    // copy all elements
    std::swap(*this, orig);  // then wap (Vector handles): strong guarantee
    return *this;
}

// move constructor
template<Element T, typename A>
Vector<T, A>::Vector(Vector<T, A>&& orig)
    : r{ std::move(orig.r.alloc), 0 }
{
    r.elem = orig.r.elem;
    r.sz = orig.r.sz;
    r.space = orig.r.space;

    orig.r.sz = 0;
    orig.r.elem = nullptr;
    orig.r.space = 0;
}

// move assignment operator
template<Element T, typename A>
Vector<T, A>& Vector<T, A>::operator=(Vector<T, A>&& orig)
{
    if (this != &orig)
    {
        // clean up existing...
        std::destroy(r.elem, r.elem + r.sz);
        r.alloc.deallocate(r.elem, r.space);

        // now steal orig's data
        r.sz = orig.r.sz;
        r.elem = orig.r.elem;
        r.space = orig.r.space;
        r.alloc = std::move(orig.r.alloc);

        // leave in orig in valid but unspecified state
        orig.r.sz = 0;
        orig.r.elem = nullptr;
        orig.r.space = 0;
    }
    return *this;
}

// destructor
template<Element T, typename A>
Vector<T, A>::~Vector()
{
    // Destroy constructed elements
    std::destroy(r.elem, r.elem + r.sz);

    // I think/hope Vector_rep's destructor will call its own alloc.deallocate() here
}

/*=======================================================*
**                                                       **
//$           Vector member functions and etc.            **
**                                                       **
 *=======================================================*/

template<Element T, typename A>
T& Vector<T, A>::at(int n)
{
    if (n < 0 || r.sz <= n)
    {
        throw std::out_of_range("[!] Out of bounds [!]\n");
    }
    return r.elem[n];
}

template<Element T, typename A>
const T& Vector<T, A>::at(int n) const
{
    if (n < 0 || r.sz <= n)
    {
        throw std::out_of_range("[!] Out of bounds! [!]\n");
    }
    return r.elem[n];
}


//$ Memory / Capacity functions 

template<Element T, typename A>
void Vector<T, A>::reserve(int newalloc)
// reserve space for Vector
{
    if (newalloc <= r.space)    // never decrease allocation
    {                  
        return;
    }

    Vector_rep<T, A> b{ r.alloc, newalloc };                // allocate new space
    std::uninitialized_move(r.elem, r.elem + r.sz, b.elem); // move

    // clear up memory before transfering ownership of p to this
    std::destroy(r.elem, r.elem + r.sz);
    // swap temporary b with r
    
    T* old_elem = r.elem;
    int old_space = r.space;

    r.elem = b.elem;
    r.space = b.space;

    b.elem = old_elem;
    b.space = old_space;
}

template<Element T, typename A>
void Vector<T, A>::resize(int newsize, T val)   // val default is T{} in declaration
{
    reserve(newsize);
    if (r.sz < newsize)
    {
        std::uninitialized_fill(r.elem + r.sz, r.elem + newsize, val);
    }
    if (newsize < r.sz)
    {
        std::destroy(r.elem + newsize, r.elem + r.sz);
    }
    r.sz = newsize;
}

template<Element T, typename A>
void Vector<T, A>::push_back(const T& val)
// increase Vector size by one; initialize the new element with d
{
    if (r.sz == r.space)
    {
        reserve((r.space == 0) ? 8 : (2 * r.space));
    }
    std::construct_at(&r.elem[r.sz], val);
    ++r.sz;
}