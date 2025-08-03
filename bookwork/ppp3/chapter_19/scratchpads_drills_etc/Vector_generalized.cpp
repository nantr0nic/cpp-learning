//$ ----- Chapter 19 Vector stuff ----- //
import std;

template<class T> concept Element = true;

template<typename T>
class Allocator 
{
public:
    // allocate space for n objects of type T
    T* allocate(int n) {             
        if (n <= 0)
        {
            return nullptr;
        }
        const std::size_t bytes{ sizeof(T) * static_cast<std::size_t>(n) };
        return static_cast<T*>(std::malloc(bytes));
    }
    // deallocate n objects of type T starting at p
    void deallocate(T* p, int n) {   
        if (p != nullptr)
        {
            std::free(p);
        }
    }
};

template<typename T, typename A = Allocator<T>>
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
public:
    using size_type = int;
    using value_type = T;
    using iterator = T*;
    using const_iterator = const T*;

private:
    Vector_rep<T, A> r; //! single letter name is a bad practice

public:
    Vector() : r{A{}, 0} { }
    explicit Vector(int s);

    Vector(std::initializer_list<value_type>);
    Vector<T, A>& operator=(std::initializer_list<value_type> lst);

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

    iterator begin() { return r.elem; }
    iterator end() { return r.elem + r.sz; }
    const_iterator begin() const { return r.elem; }
    const_iterator end() const { return r.elem + r.sz; }


    size_type size() const { return r.sz; }
    size_type capacity() const { return r.space; }

    void resize(size_type newsize, T val = T{});
    void reserve(size_type newalloc);
    void push_back(const T& val);
    void push_front(const T& val);  // not a good function! just an exercise.

    iterator erase(iterator p);
    iterator insert(iterator p, const T& val);

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
    const int reasonable_size = std::numeric_limits<int>::max();
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
Vector<T, A>::Vector(std::initializer_list<value_type> lst)
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
Vector<T, A>& Vector<T, A>::operator=(std::initializer_list<value_type> lst)
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
void Vector<T, A>::reserve(size_type newalloc)
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
    const int old_space = r.space;

    r.elem = b.elem;
    r.space = b.space;

    b.elem = old_elem;
    b.space = old_space;
}

template<Element T, typename A>
void Vector<T, A>::resize(size_type newsize, T val)   // val default is T{} in declaration
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

// "Try this" from page 828
template<Element T, typename A>
void Vector<T, A>::push_front(const T& val)
//! An inefficient function! Written for a "Try This" exercise
//$ I just realized I can check how much space there is and only
//$ make a new allocation if there is no space. That'd be better.
//$ I'll implement it tomorrow.
{
    /* I think the only way this is possible, since heap allocated and contiguous, 
    * is to copy it and add val as the first element. */
    T* p = r.alloc.allocate(r.sz + 1); // make new space + 1 for new element
    std::uninitialized_move(r.elem, r.elem + r.sz, p + 1);         // copy old to new space but at 2nd spot
    *p = val;   // make first value = val
    // clean up old memory
    std::destroy(r.elem, r.elem + r.sz);
    r.alloc.deallocate(r.elem, static_cast<std::size_t>(r.space));

    r.elem = p;   // transfer ownership
    ++r.sz;
}

template<Element T, typename A>
Vector<T, A>::iterator Vector<T,A>::erase(iterator p)
{
    if (p == end())
    {
        return p;
    }

    std::move(p + 1, r.sz, p);      // move each element one position to the left
    std::destroy_at(r.elem() + (r.sz - 1)); // destroy surplus last element
    --r.sz;
    return p;
}

template<Element T, typename A>
Vector<T, A>::iterator Vector<T, A>::insert(iterator p, const T& val)
{
    int index = p - begin();                    // save index in case of relocation
    // ^ there's some cool pointer arithmetic going on when setting index as an int
    if (size() == capacity())
    {
        reserve(size() == 0 ? 8 : 2 * size());  // make sure we have space
    }

    p = begin() + index;                            // p now points into the current allocation
    std::move_backward(p, r.sz - 1, p + 1);     // move each element one position to the right
    // ^ starts with 'right-most' element thus 'backward'
    *(begin() + index) = val;                   // "insert" val
    ++r.sz;
    return p;
}