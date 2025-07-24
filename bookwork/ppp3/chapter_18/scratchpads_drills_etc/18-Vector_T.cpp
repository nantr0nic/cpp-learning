//$ ----- 18.1.1 Replacing double with T to make template ----- //
#include <limits>
#include <stdexcept>
import std;

// global variable for educational reasons... 
int reasonable_size = std::numeric_limits<int>::max();

template<class T> concept Element = true;

template<typename T>
class allocator 
{
public:
    // ...
    // allocate space for n objects of type T
    T* allocate(int n) {             
        if (n <= 0)
        {
            return nullptr;
        }
        std::size_t bytes{ (sizeof(T) * static_cast<std::size_t>(n)) };
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

struct out_of_range { /* ... */ };

// template<typename T>        // for all types T
//     requires (Element<T>)   // such that T is an element
template<Element T, typename A = allocator<T>> // a shorter way to write the above statements (template + concept)
class Vector {
public:
    Vector() :sz{0}, elem{nullptr}, space{0} { }
    explicit Vector(int s) :sz{s}, elem{new T[s]}, space{s}
    {
        if (0 < s && s < reasonable_size)
            throw std::length_error{"Size too large for Vector"};
        
        for (int i=0; i<sz; ++i)
            elem[i]=0;
    }

    Vector(std::initializer_list<T>);
    Vector& operator=(std::initializer_list<T>);

    Vector(const Vector&);
    Vector& operator=(const Vector&);

    Vector(Vector&&);
    Vector& operator=(Vector&&);

    ~Vector() { delete[] elem; }

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
    A alloc;        // use allocatee to handle memory for elements
};

// template<typename T>
// bool operator==(const Vector<T>&, const Vector<T>&);

// template<typename T>
// bool operator!=(const Vector<T>&, const Vector<T>&);

/*
 *      main()  
*/

int main()
{


    return 0;
}

/*
 *      class definitions
*/

template<Element T, typename A>
T& Vector<T, A>::at(int n)
{
    if (n < 0 || sz <= n)
    {
        throw out_of_range();
    }
    return elem[n];
}

template<Element T, typename A>
const T& Vector<T, A>::at(int n) const
{
    if (n < 0 || sz <= n)
    {
        throw out_of_range();
    }
    return elem[n];
}

// Memory/capacity functions
template<Element T, typename A>
void Vector<T, A>::reserve(int newalloc)
// reserve space for Vector
{
    if (newalloc <= space)                  // never decrease allocation
        return;
    T* p = alloc.allocate(newalloc);        // allocate new space
    std::uninitialized_move(elem, &elem[sz], p);
    std::destroy(elem, space);
    alloc.deallocate(elem, capacity());
    elem = p;                               // make elem point to new memory
    space = newalloc;
}

template<Element T, typename A>
void Vector<T, A>::resize(int newsize, T val)
{
    reserve(newsize);
    if (sz < newsize)
    {
        std::uninitialized_fill(&elem[sz], &elem[newsize], val);
    }
    if (newsize < sz)
    {
        std::destroy(&elem[newsize], &elem[sz]);
    }
    sz = newsize;
}

template<Element T, typename A>
void Vector<T, A>::push_back(const T& val)
// increase Vector size by one; initialize the new element with d
{
    reserve((space == 0) ? 8 : (2 * space));
    std::construct_at(&elem[sz], val);
    ++sz;
}
