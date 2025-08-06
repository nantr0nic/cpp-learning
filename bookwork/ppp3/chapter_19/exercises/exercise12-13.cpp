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
    ~List();

    class iterator;     // member type: iterator

public:
    iterator begin() const { return iterator{ first }; }   // iterator to first element
    iterator end()   const { return iterator { nullptr }; }     // iterator to one beyond last element

    iterator insert(iterator p, const T& v);    // insert v before p
    iterator erase(iterator p);                 // remove p from list

    void push_back(const T& v);     // insert v at end
    void push_front(const T& v);    // insert v at front
    void pop_back();                // remove the last element
    void pop_front();               // remove the first element

    T& front() { return first->val; }         // the first element
    T& back()  { return last->val; }          // the last element
    const T& front() const { return first->val; }
    const T& back() const  { return last->val; }

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

    Link<T>* get_current() const { return curr; }

};

//$ --- initializer_list constructor --- //
template<typename T>
List<T>::List(std::initializer_list<T> lst)
    : first{ nullptr }
    , last{ nullptr }
{
    if (lst.size() == 0)
    {
        return; // empty list
    }

    for (const auto& v : lst)
    {
        push_back(v);
    }
}

template<typename T>
List<T>::~List()
{
    while (first)
    {
        Link<T>* temp{ first };
        first = first->succ;
        delete temp;
    }
}

//! must use 'typename' to tell compiler List<T>::iterator is (the return) type
template<typename T>
typename List<T>::iterator List<T>::insert(iterator p, const T& v)
// insert v BEFORE p
{
    Link<T>* curr_link{ p.get_current() };

    // if curr_link is nullptr and inserting at end()...
    if (!curr_link)
    {
        push_back(v);
        return iterator{ last };
    }

    Link<T>* new_link{ new Link<T>{ curr_link->prev, curr_link, v} };
    // if link at p has a previous link, make it point to our new link
    if (curr_link->prev)
    {
        curr_link->prev->succ = new_link;
    }
    // if it doesn't then our new link is the first element
    else 
    {
        first = new_link;
    }
    // our new link is now curr_link's previous link (inserting BEFORE)
    curr_link->prev = new_link;

    // return an iterator to the new link
    return iterator{ new_link };
}

template<typename T>
typename List<T>::iterator List<T>::erase(iterator p)
{
    Link<T>* curr_link{ p.get_current() };

    // make sure we're not erasing end() or anything null
    if (curr_link == nullptr)
    {
        return p;
    }

    // preserve the next link (even if its nullptr)
    Link<T>* next_link{ curr_link->succ };

    // the case if erasing the only element in a list
    if (curr_link->prev == nullptr && curr_link->succ == nullptr)
    {
        first = nullptr;
        last = nullptr;
        delete curr_link;
        return end();
    }
    // Update links below
    // re-link the previous link to the one being erased
    if (curr_link->prev)
    {
        curr_link->prev->succ = curr_link->succ;
    }
    // if there isn't one then reassign the "first" of the list 
    else
    {
        first = curr_link->succ;
    }
    // re-link the successive link of the one being erased
    if (curr_link->succ)
    {
        curr_link->succ->prev = curr_link->prev;
    }
    // if there isn't one... reassign last
    else
    {
        last = curr_link->prev;
    }
    // delete the current link
    delete curr_link;

    // return an iterator to the next link
    return iterator{ next_link };
}

template<typename T>
void List<T>::push_back(const T& v)
{
    Link<T>* new_link{ new Link<T>{ last, nullptr, v } };

    if (last == nullptr)    // empty list
    {
        first = last = new_link;
    }
    else
    {
        last->succ = new_link;
        last = new_link;
    }
}

template<typename T>
void List<T>::push_front(const T& v)
{
    Link<T>* new_link{ new Link<T>{ nullptr, first, v } };

    if (first == nullptr) // empty list
    {
        first = last = new_link;
    }
    else 
    {
        first->prev = new_link;
        first = new_link;
    }
}

template<typename T>
void List<T>::pop_back()
{
    if (last == nullptr) // empty list
    {
        return;
    }

    if (last->prev == nullptr) // one-item list
    {
        delete last;
        first = last = nullptr;
    }

    else
    {
        auto prev_link{ last->prev };
        prev_link->succ = nullptr;
        delete last;
        last = prev_link;
    }
}

template<typename T>
void List<T>::pop_front()
{
    if (first == nullptr) // empty list
    {
        return;
    }

    if (first->succ == nullptr) // one item list
    {
        delete first;
        first = last = nullptr;
    }

    else
    {
        auto succ_link{ first->succ };
        succ_link->prev = nullptr;
        delete first;
        first = succ_link;
    }
}

// Chapter 19 high() function
template<typename Iter>
Iter high(Iter first, Iter last)
{
    if (first == last) 
    {
        return last;
    }

    Iter highest{ first };
    for (Iter p{ first }; p != last; ++p)
    {
        if (*highest < *p)
        {
            highest = p;
        }
    }

    return highest;
}

// Helper function to print a List
template<typename T>
void print_list(const List<T>& lst, const std::string& label)
{
    std::print("{}: ", label);
    for (auto it{lst.begin()}; it != lst.end(); ++it)
    {
        std::print("{} ", *it);
    }
    std::println("");
}

//! The following test was written by an AI.
int main()
{
    std::println("=== Testing List<double> ===");
    
    // Test 1: Basic construction and push operations
    List<double> numbers{};
    numbers.push_back(3.14);
    numbers.push_back(2.71);
    numbers.push_front(1.41);
    print_list(numbers, "After pushes");
    
    // Test 2: Initializer list constructor
    List<double> more_numbers{5.5, 2.2, 8.8, 1.1, 9.9};
    print_list(more_numbers, "From initializer list");
    
    // Test 3: high() function (Exercise 12 requirement)
    auto highest{high(more_numbers.begin(), more_numbers.end())};
    if (highest != more_numbers.end())
    {
        std::println("Highest value: {}", *highest);
    }
    
    // Test 4: Insert and erase
    auto it{more_numbers.begin()};
    ++it;  // Point to second element
    more_numbers.insert(it, 7.7);
    print_list(more_numbers, "After insert");
    
    more_numbers.erase(it);  // Remove what used to be second element
    print_list(more_numbers, "After erase");
    
    // Test 5: front() and back()
    std::println("Front: {}, Back: {}", more_numbers.front(), more_numbers.back());
    
    std::println("\n=== Testing List<std::string> ===");
    
    // Test 6: String operations
    List<std::string> words{"hello", "world", "from", "list"};
    print_list(words, "String list");
    
    // Test 7: String modifications
    words.push_front("greetings");
    words.pop_back();
    print_list(words, "After modifications");
    
    // Test 8: high() with strings (lexicographical)
    auto highest_word{high(words.begin(), words.end())};
    if (highest_word != words.end())
    {
        std::println("Lexicographically highest word: {}", *highest_word);
    }
    
    // Test 9: Empty list behavior
    List<double> empty_list{};
    std::println("Empty list test - begin() == end(): {}", 
                 empty_list.begin() == empty_list.end());
    
    // Test 10: Single element operations
    List<std::string> single{"only"};
    std::println("Single element: {}", single.front());
    single.pop_back();
    std::println("After pop_back, empty: {}", 
                 single.begin() == single.end());
    
    return 0;
}