#include <string>
#include <iostream>

class Link 
{
public:
    std::string value;

    Link(const std::string& v, Link* p = nullptr, Link* s = nullptr)
        : value{ v }, prev{ p }, succ{ s } { }

    Link* insert(Link* n);                          // insert n before this object
    Link* add(Link* n);                             // insert n after this object
    Link* erase();                                  // remove this object from list

    Link* find(const std::string& s);               // find s in list
    const Link* find(const std::string& s) const;   // find s in const list (see _oper.const_)

    Link* advance(int n); //const;                  // move n positions in list
    Link* next() const { return succ; }
    Link* previous() const { return prev; }

private:
    Link* prev;
    Link* succ;
};

void print_all(Link* p)
{
    std::cout << "{ ";
    while (p)
    {
        std::cout << p->value;
        if ((p = p->next()))
            std::cout << ", ";
    }
    std::cout << " }";
}

int main()
{
    Link* norse_gods = new Link{"Thor"};
    norse_gods = norse_gods->insert(new Link{"Odin"});
    norse_gods = norse_gods->insert(new Link{"Zeus"});
    norse_gods = norse_gods->insert(new Link{"Freja"});

    Link* greek_gods = new Link{"Hera"};
    greek_gods = greek_gods->insert(new Link{"Athena"});
    greek_gods = greek_gods->insert(new Link{"Mars"});
    greek_gods = greek_gods->insert(new Link{"Poseidon"});

    Link* p = greek_gods->find("Mars");
    if (p)
        p->value = "Ares";

    Link* p2 = norse_gods->find("Zeus");
    if (p2)
    {
        if (p2 == norse_gods)
            norse_gods = p2->next();
        p2->erase();
        greek_gods = greek_gods->insert(p2);
    }

    print_all(norse_gods);
    std::cout << '\n';

    print_all(greek_gods);
    std::cout << '\n';

    return 0;
}

// ----- Link Definitions ----- //

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

Link* Link::erase()                 // remove this from list, return successor
{
    if (succ)                       // if this has a successor
        succ->prev = prev;          // set successor's predecessor to this' predecessor
    if (prev)                       // if this has predecessor
        prev->succ = succ;          // set predecessor's successor to this' successor
    return succ;
}

Link* Link::find(const std::string& s)      // find s in list, return nullptr if not found
{
    Link* current = this;
    while (current)                         // while current != nullptr
    {
        if (current->value == s)            // if found
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