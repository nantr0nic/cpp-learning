#include <initializer_list>
import std;

/*===========================================================================*
*                                Exercise 12                                 *
*  Complete the definition of list from §19.3 and get the high() example to  *
*            run. Allocate a Link to represent one past the end.             *
*                                                                            *
*                                Exercise 13                                 *
*   We don’t really need a “real” one-past-the-end Link for a list. Modify   *
*your solution to the previous exercise to use nullptr to represent a pointer*
* to the (nonexistent) one-past-the-end Link (list<Elem>::end()); that way,  *
*  the size of an empty list can be equal to the size of a single pointer.   *
 *===========================================================================*/

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
    Link<T>* first;
    Link<T>* last;

public:
    List() : first{ nullptr }, last{ nullptr } { }
    List(std::initializer_list<T> lst);

    class iterator;     // member type: iterator

public:
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

//$ --- initializer_list constructor --- //
template<typename T>
List<T>::List(std::initializer_list<T> lst)
{
}

