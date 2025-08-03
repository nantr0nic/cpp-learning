import std;

template<typename T>
struct Link 
{
    Link* prev;
    Link* succ;
    T val;
};

template<typename T>
class List 
{
private:
    // representation and implementation details
    Link<T>* first;
    Link<T>* last;
    // [...]

public:
    // ... constructors, destructor, etc.

    class iterator;     // member type: iterator

    iterator begin();   // iterator to first element
    iterator end();     // iterator to one beyond last element

    iterator insert(iterator p, const T& v);    // insert v into last after p
    iterator erase(iterator p);                 // remove p from list

    void push_back(const T& v);     // insert v at end
    void push_front(const T& v);    // insert v at front
    void pop_front();               // remove the first element
    void pop_back();                // remove the last element

    T& front();         // the first element
    T& back();          // the last element

};

template<typename T>
class List<T>::iterator 
{
private:
    Link<T>* curr;      // current link

public:
    iterator(Link<T>* p) : curr{ p } { }

    iterator& operator++() { curr = curr->succ; return *this; }     // forward
    iterator& operator--() { curr = curr->prev; return *this; }     // backward
    T& operator*() { return curr->val; }                            // get value (de-ref)

    bool operator==(const iterator& b) const { return curr == b.curr; }
    bool operator!=(const iterator& b) const { return curr != b.curr; }

};
