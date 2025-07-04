/*
***** Chapter 15 Exercises 10-13 *****

// Exercise 11:
There are two versions of find() because if a user defined an immutable (const)
list then it cannot be called by a non-const function so we need to extend
the functionality of our facilities by providing a function that does.
*/

#include <string>
#include <iostream>

using std::string;

// Link class
class Link 
{
public:
    //string value;

    Link(const string& n, const string& m, const string& v, 
        const string& w, Link* p = nullptr, Link* s = nullptr);
    
    ~Link() {};

    Link* insert(Link* n);                          // insert n before this object
    Link* add(Link* n);                             // insert n after this object
    Link* add_ordered(Link* n);                     // insert n lexicographically-ordered
    Link* erase();                                  // remove this object from list

    Link* find(const string& s);               // find s in list
    const Link* find(const string& s) const;   // find s in const list (see _oper.const_)

    Link* advance(int n); //const;                  // move n positions in list
    Link* next() const { return succ; }
    Link* previous() const { return prev; }

    // Exercise 12
    struct God_struct 
    {
        string name;
        string mythology;
        string vehicle;
        string weapon;
    };

    God_struct God;

private:
    Link* prev;
    Link* succ;
};

// Free functions declarations
void print_all(Link* p);
void delete_list(Link* p);

int main()
{
    Link* greek_gods = new Link{"Zeus", "Greek", "A Cloud", "lightning"};
    greek_gods = greek_gods->add(new Link{"Athena", "Greek", "Chariot", "Spear"});
    greek_gods = greek_gods->add(new Link{"Apollo", "Greek", 
        "Golden Chariot drawn by swans", "Bow"});
    greek_gods = greek_gods->add(new Link{"Helios", "Greek", "Fiery chariot", "The sun"});

    Link* norse_gods = new Link{"Odin", "Norse", "Eight-legged horse Sleipnir", "Gungnir"};
    norse_gods = norse_gods->add(new Link{"Thor", "Norse", 
        "Chariot pulled by two goats", "Mjolnir"});
    norse_gods = norse_gods->add(new Link{"Heimdall", "Norse", 
        "Rainbow bridge Bifrost", "Hofund"});
    norse_gods = norse_gods->add(new Link{"Tyr", "Norse", "", "Sword and shield"});

    Link* egyptian_gods = new Link{"Ra", "Egyptian", "Solar barque", "Sun Disk and Spear"};
    egyptian_gods = egyptian_gods->add(new Link{"Horus", "Egyptian", "", "Harpoon"});
    egyptian_gods = egyptian_gods->add(new Link{"Anubis", "Egyptian", 
        "Runs as a jackal", "Scepter"});
    egyptian_gods = egyptian_gods->add(new Link{"Sekhmet", "Egyptian", 
        "Sometimes rides with Ra", "Flame"});

    Link* ordered_greeks = new Link{"Zeus", "Greek", "A Cloud", "lightning"};
    ordered_greeks = ordered_greeks->add_ordered(new Link{"Athena", "Greek", "Chariot", "Spear"});
    ordered_greeks = ordered_greeks->add_ordered(new Link{"Apollo", "Greek", 
        "Golden Chariot drawn by swans", "Bow"});
    ordered_greeks = ordered_greeks->add_ordered(new Link{"Helios", "Greek", "Fiery chariot", "The sun"});

    print_all(ordered_greeks);

    delete_list(greek_gods);
    delete_list(norse_gods);
    delete_list(egyptian_gods);
    delete_list(ordered_greeks);

    return 0;
}

// ----- Free functions definitions ----- //

void print_all(Link* p)
{
    // If p points to the last element, go back to the first element before printing
    if (p->next() == nullptr && p->previous() != nullptr)
    {
        do
        {
            p = p->previous();
        } while (p->previous() != nullptr);
    }
    std::cout << "{\n";
    while (p)
    {
        std::cout << p->God.name << ", " << p->God.mythology << ", " 
        << p->God.vehicle << ", " << p->God.weapon;
        if ((p = p->next()))
            std::cout << '\n';
    }
    std::cout << "\n}";
}

void delete_list(Link* p)
{
    // Go to beginning of list
    if (p->previous() != nullptr)
    {
        do 
        {
            p = p->previous();
        } while (p->previous() != nullptr);
    }
    // Delete elements
    while (p)
    {
        Link* next = p->next();
        std::cout << "\nDeleting " << p->God.name << " at " << p << '\n';
        delete p;
        p = next;
    }
}

// ----- Link Definitions ----- //

Link::Link(const string& n, const string& m, const string& v, 
        const string& w, Link* p, Link* s)
    : God{n, m, v, w}
    , prev{ p }
    , succ{ s }
    {
    }

Link* Link::insert(Link* n)         // insert n before this object; return n
{
    if (n == nullptr)               // nothing to insert
        return this;
    n->succ = this;                 // p comes after n
    if (prev)
        prev->succ = n;
    n->prev = prev;                 // p's predecessor becomes n's predecessor
    prev = n;                       // n becomes p's predecessor
    return n;
}

Link* Link::add(Link* n)            // insert n after this object; return n
{
    if (n == nullptr)               // nothing to add
        return this;
    n->prev = this;                 // this comes before n
    n->succ = succ;                 // this' successor becomes n's successor (including nullptr)
    if (succ)                       // if this object has (non-null) successor,
        succ->prev = n;             // n becomes this's successor's predecessor
    succ = n;                       // this object's successor becomes n
    return n;
}

Link* Link::add_ordered(Link* n)    // Add n and place lexicographically (alphabetically)
{                                   // Assuming names use capital first letter
    if (n == nullptr)
        return this;

    Link* p = this;

    // Go to beginning of list
    if (p->prev != nullptr)
    {
        do
        {
            p = p->prev;
        } while (p->prev != nullptr);
    }
    // Advance through the list until we find a lesser or equal value
    while (p->succ != nullptr && p->God.name < n->God.name)
    {
        p = p->succ;
    }
    // Decide whether to insert or add
    if (p->God.name > n->God.name)
        p->insert(n);        // insert n before p
    else
        p->add(n);           // add after p (I think only if on end of list)

    // Always return the actual head of the list
    Link* head = this;
    while (head->prev != nullptr)
        head = head->prev;
    return head;
}

Link* Link::erase()                 // remove this from list, return successor
{
    if (succ)                       // if this has a successor
        succ->prev = prev;          // set successor's predecessor to this' predecessor
    if (prev)                       // if this has predecessor
        prev->succ = succ;          // set predecessor's successor to this' successor
    return succ;
}

Link* Link::find(const string& s)      // find s in list, return nullptr if not found
{
    Link* current = this;
    while (current)                         // while current != nullptr
    {
        if (current->God.name == s)            // if found
            return current;                 // return it
        current = current->succ;            // if not, move on to successor (until nullptr)
    }
    return nullptr;
}

Link* Link::advance(int n)          // move n positions in list; return nullptr for "not found"
{                                   // positive n moves forward, negative backward
    Link* p = this;
    if (p == nullptr)
        return nullptr;
    while (0 < n)
    {
        --n;
        if (p->succ)
            p = p->succ;
        else
            return nullptr;
    }
    while (n < 0)
    {
        ++n;
        if (p->prev)
            p = p->prev;
        else
            return nullptr;
    }
    return p;
}