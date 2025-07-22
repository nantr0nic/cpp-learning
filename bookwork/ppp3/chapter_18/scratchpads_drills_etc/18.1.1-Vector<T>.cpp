//$ ----- 18.1.1 Replacing double with T to make template ----- //
#include <initializer_list>


template<typename T>        // for all types T
    requires (Element<T>())   // such that T is an element
//template<Element T> // a shorter way to write the above statements (template + concept)
class Vector {
public:
    Vector() :sz{0}, elem{nullptr}, space{0} { }
    explicit Vector(int s) :sz{s}, elem{new T[s]}, space{s}
    {
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
    T& operator[](int n) { return elem[n]; }
    const T& operator[](int n) const { return elem[n]; }

    int size() const { return sz; }
    int capacity() const { return space; }

    void resize(int newsize);
    void push_back(const T& d);
    void reserve(int newalloc);

    T* begin() const { return elem; }
    T* end() const { return elem+sz; }

private:
    int sz;
    T* elem;
    int space;

};

template<typename T>
bool operator==(const Vector<T>&, const Vector<T>&);

template<typename T>
bool operator!=(const Vector<T>&, const Vector<T>&);
